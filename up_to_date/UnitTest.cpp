#define CATCH_CONFIG_MAIN
#include "Catch.hpp"
#include "Lanes.h"
#include "Driver.h"
#include "VehicleBase.h"
#include "Counter.h"
#include <memory>
#include <iostream>

using namespace std;

TEST_CASE("Testing Driver"){
	Driver d{"input_file_format.txt"};

	//note that these tests passing are dependent on the values given in the sample input
	SECTION("Generating a vehicle"){

		//test for some random value that the correct vehicles are being constructed in generateVehicles
		double rand = .01;
		auto vb_ptr = d.generateVehicles(rand, Direction::north);
		REQUIRE(vb_ptr != nullptr);
		REQUIRE(vb_ptr->getVehicleID() == 0);
		REQUIRE(vb_ptr->getVehicleType() == VehicleType::car);
		REQUIRE(vb_ptr->getVehicleTurn() == Turn::left);

		vb_ptr = d.generateVehicles(rand, Direction::south);
		REQUIRE(vb_ptr != nullptr);
		REQUIRE(vb_ptr->getVehicleID() == 1);
		REQUIRE(vb_ptr->getVehicleType() == VehicleType::car);
		REQUIRE(vb_ptr->getVehicleTurn() == Turn::right);

		vb_ptr = d.generateVehicles(rand, Direction::west);
		REQUIRE(vb_ptr != nullptr);
		REQUIRE(vb_ptr->getVehicleID() == 2);
		REQUIRE(vb_ptr->getVehicleType() == VehicleType::car);
		REQUIRE(vb_ptr->getVehicleTurn() == Turn::right);

		vb_ptr = d.generateVehicles(rand, Direction::east);
		REQUIRE(vb_ptr != nullptr);
		REQUIRE(vb_ptr->getVehicleID() == 3);
		REQUIRE(vb_ptr->getVehicleType() == VehicleType::car);
		REQUIRE(vb_ptr->getVehicleTurn() == Turn::right);

		//test a high random number will cause no vehicles to generate in any direction
		rand = .99;
		vb_ptr = d.generateVehicles(rand, Direction::east);
		REQUIRE(vb_ptr == nullptr);

		vb_ptr = d.generateVehicles(rand, Direction::west);
		REQUIRE(vb_ptr == nullptr);

		vb_ptr = d.generateVehicles(rand, Direction::north);
		REQUIRE(vb_ptr == nullptr);

		vb_ptr = d.generateVehicles(rand, Direction::south);
		REQUIRE(vb_ptr == nullptr);

	}
}

TEST_CASE("Testing lanes"){
	Driver d{"input_file_format.txt"};
	Lanes lanes{5};
	
	SECTION("Adding Vehicle to queue"){

		//test adding to northbound queue
		shared_ptr<VehicleBase> vb_ptr = shared_ptr<VehicleBase>(new VehicleBase(VehicleType::car, Direction::north, Turn::straight));
		lanes.new_vehicle(vb_ptr);


		REQUIRE(lanes.nb_qq.front() != nullptr);
		REQUIRE(lanes.nb_qq.front()->getVehicleType() == VehicleType::car);
		REQUIRE(lanes.nb_qq.front()->getVehicleTurn() == Turn::straight);
		REQUIRE(lanes.nb_qq.front()->getVehicleOriginalDirection() == Direction::north);
		REQUIRE(lanes.nb_qq.front()->getVehicleID() == 4);

		//test adding to southbound queue
		vb_ptr = shared_ptr<VehicleBase>(new VehicleBase(VehicleType::truck, Direction::south, Turn::left));
		lanes.new_vehicle(vb_ptr);

		REQUIRE(lanes.sb_qq.front() != nullptr);
		REQUIRE(lanes.sb_qq.front()->getVehicleType() == VehicleType::truck);
		REQUIRE(lanes.sb_qq.front()->getVehicleTurn() == Turn::left);
		REQUIRE(lanes.sb_qq.front()->getVehicleOriginalDirection() == Direction::south);
		REQUIRE(lanes.sb_qq.front()->getVehicleID() == 5);

		//test adding to eastbound queue
		vb_ptr = shared_ptr<VehicleBase>(new VehicleBase(VehicleType::suv, Direction::east, Turn::right));
		lanes.new_vehicle(vb_ptr);

		REQUIRE(lanes.eb_qq.front() != nullptr);
		REQUIRE(lanes.eb_qq.front()->getVehicleType() == VehicleType::suv);
		REQUIRE(lanes.eb_qq.front()->getVehicleTurn() == Turn::right);
		REQUIRE(lanes.eb_qq.front()->getVehicleOriginalDirection() == Direction::east);
		REQUIRE(lanes.eb_qq.front()->getVehicleID() == 6);


		//test adding to westbound queue
		vb_ptr = shared_ptr<VehicleBase>(new VehicleBase(VehicleType::suv, Direction::west, Turn::straight));
		lanes.new_vehicle(vb_ptr);

		REQUIRE(lanes.wb_qq.front() != nullptr);
		REQUIRE(lanes.wb_qq.front()->getVehicleType() == VehicleType::suv);
		REQUIRE(lanes.wb_qq.front()->getVehicleTurn() == Turn::straight);
		REQUIRE(lanes.wb_qq.front()->getVehicleOriginalDirection() == Direction::west);
		REQUIRE(lanes.wb_qq.front()->getVehicleID() == 7);
	}


	SECTION("Checking advance lanes - straight"){
		int til_red = 10;
		bool ns_red = false;
		shared_ptr<VehicleBase> vb_ptr = shared_ptr<VehicleBase>(new VehicleBase(VehicleType::car, Direction::north, Turn::straight));
		lanes.new_vehicle(vb_ptr);
		lanes.addFromQ();
		lanes.advanceBottoms();
		lanes.addFromQ();
		lanes.advanceBottoms();
		REQUIRE(lanes.nb_lane[1] == vb_ptr);
		REQUIRE(lanes.nb_lane[2] == vb_ptr);

		lanes.advanceBottoms();
		lanes.advanceBottoms();

		lanes.advanceTops(ns_red, til_red); // goes into intersection with green light
		lanes.advanceBottoms();
		REQUIRE(lanes.nb_lane[4] == vb_ptr);
		REQUIRE(lanes.nb_lane[5] == vb_ptr);

		lanes.advanceTops(ns_red, til_red);
		lanes.advanceTops(ns_red, til_red);
		lanes.advanceTops(ns_red, til_red);

		REQUIRE(lanes.nb_lane[7] == vb_ptr);
		REQUIRE(lanes.nb_lane[8] == vb_ptr); // goes through intersection
	}

	SECTION("Checking Turn Right"){
		int til_red = 10;
		bool ns_red = false;
		shared_ptr<VehicleBase> vb_ptr = shared_ptr<VehicleBase>(new VehicleBase(VehicleType::car, Direction::north, Turn::right));
		lanes.nb_lane[3] = lanes.nb_lane[4] = vb_ptr;

		lanes.advanceTops(ns_red, til_red); // goes into intersection with green light
		lanes.advanceBottoms();

		lanes.advanceTops(ns_red, til_red); // First section turns
		lanes.advanceTops(ns_red, til_red); // second section turns

		REQUIRE(lanes.eb_lane[7] == vb_ptr);
		REQUIRE(lanes.eb_lane[8] == vb_ptr);

	}

	SECTION("Checking Stop at light on Red"){
		int til_red = 10;
		bool ns_red = true;
		shared_ptr<VehicleBase> vb_ptr = shared_ptr<VehicleBase>(new VehicleBase(VehicleType::car, Direction::north, Turn::right));
		lanes.nb_lane[3] = lanes.nb_lane[4] = vb_ptr;

		lanes.advanceTops(ns_red, til_red); // goes into intersection with green light
		lanes.advanceBottoms();

		lanes.advanceTops(ns_red, til_red); // wont go
		lanes.advanceTops(ns_red, til_red); // wont go

		REQUIRE(lanes.nb_lane[3] == vb_ptr); // stayed in the same place
		REQUIRE(lanes.nb_lane[4] == vb_ptr);

	}

	SECTION("Checking Stop at light on Yellow if Can't make it"){
		int til_red = 3;
		bool ns_red = false;
		shared_ptr<VehicleBase> vb_ptr = shared_ptr<VehicleBase>(new VehicleBase(VehicleType::truck, Direction::north, Turn::straight));
		lanes.nb_lane[0] = lanes.nb_lane[1] = lanes.nb_lane[2] = lanes.nb_lane[3] = vb_ptr;

		lanes.advanceTops(ns_red, til_red); // goes into intersection with green light
		lanes.advanceBottoms();

		lanes.advanceTops(ns_red, til_red); // wont go
		lanes.advanceBottoms();
		lanes.advanceTops(ns_red, til_red); // wont go
		lanes.advanceBottoms();

		REQUIRE(lanes.nb_lane[1] == vb_ptr); // only moves forward 1
		REQUIRE(lanes.nb_lane[2] == vb_ptr);
		REQUIRE(lanes.nb_lane[3] == vb_ptr);
		REQUIRE(lanes.nb_lane[4] == vb_ptr);

	}

	SECTION("Checking Waiting for car to clear lane before going on green"){
		int til_red = 3;
		bool ns_red = false;
		shared_ptr<VehicleBase> vb_ptr = shared_ptr<VehicleBase>(new VehicleBase(VehicleType::car, Direction::north, Turn::straight));
		shared_ptr<VehicleBase> vb_ptr2 = shared_ptr<VehicleBase>(new VehicleBase(VehicleType::suv, Direction::north, Turn::straight));
		lanes.nb_lane[3] = lanes.nb_lane[4] = vb_ptr;
		lanes.eb_lane[5] = lanes.eb_lane[6] = lanes.eb_lane[7] = vb_ptr2;

		lanes.advanceTops(ns_red, til_red); // green light but car in front
		lanes.advanceBottoms();

		REQUIRE(lanes.nb_lane[3] == vb_ptr);
		REQUIRE(lanes.nb_lane[4] == vb_ptr);

		lanes.advanceTops(ns_red, til_red); // near miss
		lanes.advanceBottoms();

		REQUIRE(lanes.nb_lane[4] == vb_ptr);
		REQUIRE(lanes.nb_lane[5] == vb_ptr);

	}
}

TEST_CASE("Testing VehicleBase"){

	SECTION("Copy Constructor"){
		VehicleBase vb{VehicleType::car, Direction::north, Turn::straight};
		VehicleBase vbCopy(vb);

		REQUIRE(vbCopy.getVehicleID() == vb.getVehicleID());
		REQUIRE(vbCopy.getVehicleType() == vb.getVehicleType());
		REQUIRE(vbCopy.getVehicleTurn() == vb.getVehicleTurn());
		REQUIRE(vbCopy.getVehicleOriginalDirection() == vb.getVehicleOriginalDirection());
	}

	SECTION("Move Constructor"){
		VehicleBase vb{VehicleType::car, Direction::north, Turn::straight};
		VehicleBase vbCopy(move(vb));

		REQUIRE(vbCopy.getVehicleID() != vb.getVehicleID());
		REQUIRE(vbCopy.getVehicleType() != vb.getVehicleType());
		REQUIRE(vbCopy.getVehicleTurn() != vb.getVehicleTurn());
		REQUIRE(vbCopy.getVehicleOriginalDirection() != vb.getVehicleOriginalDirection());
	}

	SECTION("Copy Assignment Operator"){
		VehicleBase vb{VehicleType::car, Direction::north, Turn::straight};
		VehicleBase vbCopy = vb;

		REQUIRE(vbCopy.getVehicleID() == vb.getVehicleID());
		REQUIRE(vbCopy.getVehicleType() == vb.getVehicleType());
		REQUIRE(vbCopy.getVehicleTurn() == vb.getVehicleTurn());
		REQUIRE(vbCopy.getVehicleOriginalDirection() == vb.getVehicleOriginalDirection());
	}

	SECTION("Move Assignment Operator"){
		VehicleBase vb{VehicleType::car, Direction::north, Turn::straight};
		VehicleBase vbCopy = move(vb);

		REQUIRE(vbCopy.getVehicleID() != vb.getVehicleID());
		REQUIRE(vbCopy.getVehicleType() != vb.getVehicleType());
		REQUIRE(vbCopy.getVehicleTurn() != vb.getVehicleTurn());
		REQUIRE(vbCopy.getVehicleOriginalDirection() != vb.getVehicleOriginalDirection());
	}
}

TEST_CASE("Testing Generate Correction Proportions"){
	Driver d{"input_file_format.txt"};
	mt19937 randomNumberGenerator;
  uniform_real_distribution<double> rand_double(0.0, 1.0);

	SECTION("Counting Cars"){
		int time = 0;
		Counter c;
		double rand;
		while(time < 1000){
			rand = rand_double(randomNumberGenerator);
			auto vb_ptr = d.generateVehicles(rand, Direction::north);
			if(vb_ptr != nullptr) c.count(vb_ptr);
			vb_ptr = d.generateVehicles(rand, Direction::south);
			if(vb_ptr != nullptr) c.count(vb_ptr);
			vb_ptr = d.generateVehicles(rand, Direction::east);
			if(vb_ptr != nullptr) c.count(vb_ptr);
			vb_ptr = d.generateVehicles(rand, Direction::west);
			if(vb_ptr != nullptr) c.count(vb_ptr);

			time++;
		}
		vector<double> counted = c.stats(time);
		vector<double> inputs = d.stats();
		double margin;
		for(int i = 0; i < inputs.size(); i++){
			margin = (inputs[i] - counted[i])*(inputs[i] - counted[i]);
			margin = margin/inputs[i];
			REQUIRE(margin < .05);
		}

	}
}

