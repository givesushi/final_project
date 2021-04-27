#ifndef __DRIVER_H__
#define __DRIVER_H__

#include "VehicleBase.h"
#include "Animator.h"
#include "Lanes.h"
#include <iostream>
#include <fstream>
#include <random>
#include <memory>
using namespace std;

class Driver{

public:

  //input variables from file
  int maximum_simulated_time;
  int number_of_sections_before_intersection;
  int green_north_south;
  int yellow_north_south;
  int red_north_south; //implicit
  int green_east_west;
  int yellow_east_west;
  int red_east_west; //implicit

  double prob_new_vehicle_eastbound;
  double prob_new_vehicle_westbound;
  double prob_new_vehicle_northbound;
  double prob_new_vehicle_southbound;

  double proportion_of_cars;
  double proportion_of_SUVs;
  double proportion_of_trucks; //implicit

  double proportion_left_turn_cars;
  double proportion_right_turn_cars;
  double proportion_straight_cars; //implicit
  double proportion_left_turn_SUVs;
  double proportion_right_turn_SUVs;
  double proportion_straight_SUVs; //implicit
  double proportion_left_turn_trucks;
  double proportion_right_turn_trucks;
  double proportion_straight_trucks; //implicit

  //variables for generating vehicles.
  double east_car;
  double east_car_l;
  double east_car_r;
  double east_car_s;
  double east_SUV;
  double east_SUV_l;
  double east_SUV_r;
  double east_SUV_s;
  double east_truck;
  double east_truck_l;
  double east_truck_r;
  double east_truck_s;

  double west_car;
  double west_car_l;
  double west_car_r;
  double west_car_s;
  double west_SUV;
  double west_SUV_l;
  double west_SUV_r;
  double west_SUV_s;
  double west_truck;
  double west_truck_l;
  double west_truck_r;
  double west_truck_s;

  double south_car;
  double south_car_l;
  double south_car_r;
  double south_car_s;
  double south_SUV;
  double south_SUV_l;
  double south_SUV_r;
  double south_SUV_s;
  double south_truck;
  double south_truck_l;
  double south_truck_r;
  double south_truck_s;

  double north_car;
  double north_car_l;
  double north_car_r;
  double north_car_s;
  double north_SUV;
  double north_SUV_l;
  double north_SUV_r;
  double north_SUV_s;
  double north_truck;
  double north_truck_l;
  double north_truck_r;
  double north_truck_s;


  //FUNCTIONS
  //constructor
  Driver(string infile);
  ~Driver();

  //construct and add vehicles to lanes in anim
  shared_ptr<VehicleBase> generateVehicles(double rand, Direction start);

  vector<double> stats();

};

#endif
