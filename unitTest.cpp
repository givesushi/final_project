#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "VehicleBase.h"
#include "Animator.h"
#include "Driver.h"
#include <string>

TEST_CASE("Testing Driver"){
	Driver d{5};
	SECTION("Making a new Vehicle"){
		d.new_vehicle(VehicleType::car, Direction::north, Turn::straight);
		pair<int,int> first_coordinate(0,(int)Direction::north);
		pair<int,int> second_coordinate(-1, (int)Direction::north);
		int id = d.coordinate_ID_map.at(first_coordinate);
		REQUIRE(id == 0);
		id = d.coordinate_ID_map.at(first_coordinate);
		REQUIRE(id == 0);
		auto vb = d.ID_VehicleBase_map.at(id);
		cout << &vb << endl;
		string output = "";
		for(auto it = d.coordinate_ID_map.begin(); it != d.coordinate_ID_map.end(); ++it){
			pair<int,int> coordinate_pair = it->first;
			output += "(" + to_string(get<0>(coordinate_pair)) + ", " + to_string(get<1>(coordinate_pair)) + ")";
		}
		REQUIRE(output == "(-1, 0)(0, 0)");
	}

	SECTION("Two Vehicles Same Lane"){
		d.new_vehicle(VehicleType::car, Direction::north, Turn::straight);
		d.new_vehicle(VehicleType::truck, Direction::north, Turn::straight);
		string output = "";
		for(auto it = d.coordinate_ID_map.begin(); it != d.coordinate_ID_map.end(); ++it){
			pair<int,int> coordinate_pair = it->first;
			output += "(" + to_string(get<0>(coordinate_pair)) + ", " + to_string(get<1>(coordinate_pair)) + ")";
		}
		REQUIRE(output == "(-5, 0)(-4, 0)(-3, 0)(-2, 0)(-1, 0)(0, 0)");
	}
	// After this test I noticed that vehicle bases were being destructed with ID 2 should be 0 and 1
	// Realized that it was because of the first section incremented ID

	SECTION("Testing ptr_lane..."){  // want to make sure it is writing to vector
		d.new_vehicle(VehicleType::car, Direction::north, Turn::straight);
		auto vb_ptrs = d.ptr_lane(Direction::north);
		for(auto vb : vb_ptrs)
			cout << vb << endl;
		// no requirements but should print an address followed by many 0x0
	}

	SECTION("Testing closed addition method"){
		pair<int,int> p1 = make_pair(1,1);
		pair<int,int> p2 = make_pair(1,3);
		auto p3 = d.closed_addition(p1,p1);
		bool test = (get<0>(p3) == 2 && get<1>(p3) == 2);
		REQUIRE(test);
		p3 = d.closed_addition(p1,p2);
		test = (get<0>(p3) == 2 && get<1>(p3) == 0);
		REQUIRE(test);
	}
}

TEST_CASE("Testing progress lanes"){
	Driver d{5};
	d.new_vehicle(VehicleType::car, Direction::north ,Turn::right );
	d.new_vehicle(VehicleType::car, Direction::south ,Turn::straight );
	d.new_vehicle(VehicleType::car, Direction::east ,Turn::straight );
	d.new_vehicle(VehicleType::car, Direction::west ,Turn::right );

	Animator anim{5};
	anim.setLightNorthSouth(LightColor::green);
	anim.setLightEastWest(LightColor::red);

	char dummy;

	int t = 0;
	while(t < 30){
		anim.setVehiclesNorthbound(d.ptr_lane(Direction::north));
		anim.setVehiclesEastbound(d.ptr_lane(Direction::east));
		anim.setVehiclesSouthbound(d.ptr_lane(Direction::south));
		anim.setVehiclesWestbound(d.ptr_lane(Direction::west));

		d.progress_lanes(false);

		anim.draw(t);
		cin.get(dummy);
		t++;
	}


}
