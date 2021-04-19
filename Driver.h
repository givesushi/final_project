#include "VehicleBase.h"
#include "Animator.h"
#include <iostream>
#include <fstream>
#include <random>
using namespace std;

class Driver{

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


  //FUNCTIONS

public:
  //constructor
  Driver(string infile);
  ~Driver();

  //construct and add vehicles to lanes in anim
  void generateVehicles(double rand, Animator anim);

  //run the simulation
  void run();

};
