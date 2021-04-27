#define CATCH_CONFIG_MAIN
#include "Catch.hpp"
#include "Lanes.h"
#include "Driver.h"
#include "VehicleBase.h"
#include <memory>
#include <iostream>

using namespace std;

TEST_CASE("Testing Driver"){
	Driver d{"input_file_format.txt"};

	SECTION("Generating a vehicle"){
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
	}

	SECTION("Adding Vehicle to queue"){
		Lanes lanes{5};
		shared_ptr<VehicleBase> vb_ptr = shared_ptr<VehicleBase>(new VehicleBase(VehicleType::car, Direction::north, Turn::straight));
		lanes.new_vehicle(vb_ptr);
		
	}
}

TEST_CASE("Testing lanes"){
	Driver d{"input_file_format.txt"};
	Lanes lanes{5};

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
