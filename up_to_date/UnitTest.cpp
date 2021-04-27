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
