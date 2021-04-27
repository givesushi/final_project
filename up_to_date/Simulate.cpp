#include "Driver.h"
#include "Animator.h"
#include "Lanes.h"
#include "VehicleBase.h"
#include <memory>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]){

  //Driver object to get all the inputs.
	Driver driver{argv[1]};

  // Random number generator variables
  // random number seed given by user.
	int seed = stoi(argv[2]);

  mt19937 randomNumberGenerator;
  uniform_real_distribution<double> rand_double(0.0, 1.0);
	randomNumberGenerator.seed(seed);
  double rand;

  Animator anim(driver.number_of_sections_before_intersection);
  Lanes lanes(driver.number_of_sections_before_intersection);

  // VehicleBase vb_n(VehicleType::suv, Direction::north, Turn::right);
  // VehicleBase vb_n1(VehicleType::car, Direction::north, Turn::right);
  // VehicleBase vb_s(VehicleType::car, Direction::south, Turn::straight);
  // VehicleBase vb_s1(VehicleType::car, Direction::south, Turn::right);
  // VehicleBase vb_e(VehicleType::car, Direction::east, Turn::straight);
  // VehicleBase vb_e1(VehicleType::car, Direction::east, Turn::right);
  // VehicleBase vb_w(VehicleType::car, Direction::west, Turn::straight);
  // VehicleBase vb_w1(VehicleType::car, Direction::west, Turn::right);
	//
  // lanes.new_vehicle(&vb_n);
  // lanes.new_vehicle(&vb_s);
  // lanes.new_vehicle(&vb_e);
  // lanes.new_vehicle(&vb_w);


  bool ns_red = false;

	int stoplight_timer = 0, til_red;

  char dummy;
  int clock = 0;

  anim.setLightNorthSouth(LightColor::green);
  anim.setLightEastWest(LightColor::red);

  while(clock <= driver.maximum_simulated_time){

    rand = rand_double(randomNumberGenerator);

		lanes.new_vehicle(driver.generateVehicles(rand, Direction::north));
		lanes.new_vehicle(driver.generateVehicles(rand, Direction::south));
		lanes.new_vehicle(driver.generateVehicles(rand, Direction::east));
		lanes.new_vehicle(driver.generateVehicles(rand, Direction::west));

		if(ns_red){
			til_red = driver.green_east_west + driver.yellow_east_west - stoplight_timer;
			if(stoplight_timer == driver.green_east_west){
				anim.setLightEastWest(LightColor::yellow);
			}else if(stoplight_timer == driver.green_east_west + driver.yellow_east_west){
				anim.setLightEastWest(LightColor::red);
				anim.setLightNorthSouth(LightColor::green);
				ns_red = !ns_red;
				til_red = driver.green_north_south + driver.yellow_north_south;
				stoplight_timer = 0;
			}
		}else{
			til_red = driver.green_north_south + driver.yellow_north_south - stoplight_timer;
			if(stoplight_timer == 0){
				anim.setLightNorthSouth(LightColor::green);
			}else if (stoplight_timer == driver.green_north_south){
				anim.setLightNorthSouth(LightColor::yellow);
			}else if(stoplight_timer == driver.green_north_south + driver.yellow_north_south){
				anim.setLightNorthSouth(LightColor::red);
				anim.setLightEastWest(LightColor::green);
				ns_red = !ns_red;
				til_red = driver.green_east_west + driver.yellow_east_west;
				stoplight_timer = 0;
			}
		}

    anim.setVehiclesNorthbound(lanes.get_nb_lane());
    anim.setVehiclesWestbound(lanes.get_wb_lane());
    anim.setVehiclesSouthbound(lanes.get_sb_lane());
    anim.setVehiclesEastbound(lanes.get_eb_lane());

    anim.draw(clock);

    cin.get(dummy);

    lanes.advanceTops(ns_red,til_red);
    lanes.advanceBottoms();
    lanes.addFromQ();

    clock++;
		stoplight_timer++;
  }

  return 0;
}
