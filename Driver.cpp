#include "Driver.h"

//constructor
Driver::Driver(string infile){
  std::ifstream input {infile};
  if(!input){
    cout << "Error: Could not open file:" << infile << endl;
  }

  // get input from file
  string str;
  string key;
  int val;
  double d_val;
  while(getline(input, str)){
    key = str.substr(0,str.find(":"));
    val = stoi(str.substr(str.find(":")+1));
    d_val = stod(str.substr(str.find(":")+1));

      //set values of input variables
      if(key == "maximum_simulated_time"){maximum_simulated_time = val;}
      if(key == "number_of_sections_before_intersection"){number_of_sections_before_intersection = val;}
      if(key == "green_north_south"){green_north_south = val;}
      if(key == "yellow_north_south"){yellow_north_south = val;}
      if(key == "green_east_west"){green_east_west = val;}
      if(key == "yellow_east_west"){yellow_east_west = val;}
      if(key == "prob_new_vehicle_eastbound"){prob_new_vehicle_eastbound = d_val;}
      if(key == "prob_new_vehicle_westbound"){prob_new_vehicle_westbound = d_val;}
      if(key == "prob_new_vehicle_northbound"){prob_new_vehicle_northbound = d_val;}
      if(key == "prob_new_vehicle_southbound"){prob_new_vehicle_southbound = d_val;}
      if(key == "proportion_of_cars"){proportion_of_cars = d_val;}
      if(key == "proportion_of_SUVs"){proportion_of_SUVs = d_val;}
      if(key == "proportion_left_turn_cars"){proportion_left_turn_cars = d_val;}
      if(key == "proportion_right_turn_cars"){proportion_right_turn_cars = d_val;}
      if(key == "proportion_left_turn_SUVs"){proportion_left_turn_SUVs = d_val;}
      if(key == "proportion_right_turn_SUVs"){proportion_right_turn_SUVs = d_val;}
      if(key == "proportion_left_turn_trucks"){proportion_left_turn_trucks = d_val;}
      if(key == "proportion_right_turn_trucks"){proportion_right_turn_trucks = d_val;}
  }

  input.close();

  //implict variables based on explictly input variables.
  red_north_south = green_east_west + yellow_east_west;
  red_east_west = green_north_south + yellow_north_south;
  proportion_of_trucks = 1 - proportion_of_cars - proportion_of_SUVs;
  proportion_straight_cars = 1 - proportion_left_turn_cars - proportion_right_turn_cars;
  proportion_straight_SUVs = 1 - proportion_left_turn_SUVs - proportion_right_turn_SUVs;
  proportion_straight_trucks = 1 - proportion_left_turn_trucks - proportion_right_turn_trucks;

  //values for generating new vehicles each clock tick
  //EAST
  double east_car = prob_new_vehicle_eastbound * proportion_of_cars;
  double east_car_l = east_car * proportion_left_turn_cars;
  double east_car_r = east_car_l + (east_car * proportion_right_turn_cars);
  double east_car_s = east_car_r + (east_car * proportion_straight_cars);

  double east_SUV = (prob_new_vehicle_eastbound * proportion_of_SUVs);
  double east_SUV_l = east_car_s + (east_SUV * proportion_left_turn_SUVs);
  double east_SUV_r = east_SUV_l + (east_SUV * proportion_right_turn_SUVs);
  double east_SUV_s = east_SUV_r + (east_SUV * proportion_straight_SUVs);

  double east_truck = (prob_new_vehicle_eastbound * proportion_of_trucks);
  double east_truck_l = east_SUV_s + (east_truck * proportion_left_turn_trucks);
  double east_truck_r = east_truck_l + (east_truck * proportion_right_turn_trucks);
  double east_truck_s = east_truck_r + (east_truck * proportion_straight_trucks);

  //WEST
  double west_car = prob_new_vehicle_westbound * proportion_of_cars;
  double west_car_l = west_car * proportion_left_turn_cars;
  double west_car_r = west_car_l + (west_car * proportion_right_turn_cars);
  double west_car_s = west_car_r + (west_car * proportion_straight_cars);

  double west_SUV = (prob_new_vehicle_westbound * proportion_of_SUVs);
  double west_SUV_l = west_car_s + (west_SUV * proportion_left_turn_SUVs);
  double west_SUV_r = west_SUV_l + (west_SUV * proportion_right_turn_SUVs);
  double west_SUV_s = west_SUV_r + (west_SUV * proportion_straight_SUVs);

  double west_truck = (prob_new_vehicle_westbound * proportion_of_trucks);
  double west_truck_l = west_SUV_s + (west_truck * proportion_left_turn_trucks);
  double west_truck_r = west_truck_l + (west_truck * proportion_right_turn_trucks);
  double west_truck_s = west_truck_r + (west_truck * proportion_straight_trucks);

  //SOUTH
  double south_car = prob_new_vehicle_southbound * proportion_of_cars;
  double south_car_l = south_car * proportion_left_turn_cars;
  double south_car_r = south_car_l + (south_car * proportion_right_turn_cars);
  double south_car_s = south_car_r + (south_car * proportion_straight_cars);

  double south_SUV = (prob_new_vehicle_southbound * proportion_of_SUVs);
  double south_SUV_l = south_car_s + (south_SUV * proportion_left_turn_SUVs);
  double south_SUV_r = south_SUV_l + (south_SUV * proportion_right_turn_SUVs);
  double south_SUV_s = south_SUV_r + (south_SUV * proportion_straight_SUVs);

  double south_truck = (prob_new_vehicle_southbound * proportion_of_trucks);
  double south_truck_l = south_SUV_s + (south_truck * proportion_left_turn_trucks);
  double south_truck_r = south_truck_l + (south_truck * proportion_right_turn_trucks);
  double south_truck_s = south_truck_r + (south_truck * proportion_straight_trucks);

  //NORTH
  double north_car = prob_new_vehicle_northbound * proportion_of_cars;
  double north_car_l = north_car * proportion_left_turn_cars;
  double north_car_r = north_car_l + (north_car * proportion_right_turn_cars);
  double north_car_s = north_car_r + (north_car * proportion_straight_cars);

  double north_SUV = (prob_new_vehicle_northbound * proportion_of_SUVs);
  double north_SUV_l = north_car_s + (north_SUV * proportion_left_turn_SUVs);
  double north_SUV_r = north_SUV_l + (north_SUV * proportion_right_turn_SUVs);
  double north_SUV_s = north_SUV_r + (north_SUV * proportion_straight_SUVs);

  double north_truck = (prob_new_vehicle_northbound * proportion_of_trucks);
  double north_truck_l = north_SUV_s + (north_truck * proportion_left_turn_trucks);
  double north_truck_r = north_truck_l + (north_truck * proportion_right_turn_trucks);
  double north_truck_s = north_truck_r + (north_truck * proportion_straight_trucks);

}

void Driver::generateVehicles(double rand, Lanes lanes){
  //Generate a new vehicle based on random number for each lane.
  //EAST
  if(rand < east_truck_s){
    if(rand < east_car_l){
      lanes.new_vehicle(Direction::east, VehicleType::car, Turn::left);
    }else if(rand < east_car_r){
			lanes.new_vehicle(Direction::east, VehicleType::car, Turn::right);
    }else if(rand < east_car_s){
			lanes.new_vehicle(Direction::east, VehicleType::car, Turn::straight);
    }else if(rand < east_SUV_l){
			lanes.new_vehicle(Direction::east, VehicleType::suv, Turn::left);
    }else if(rand < east_SUV_r){
			lanes.new_vehicle(Direction::east, VehicleType::suv, Turn::right);
    }else if(rand < east_SUV_s){
			lanes.new_vehicle(Direction::east, VehicleType::suv, Turn::straight);
    }else if(rand < east_truck_l){
			lanes.new_vehicle(Direction::east, VehicleType::truck, Turn::left);
    }else if(rand < east_truck_r){
			lanes.new_vehicle(Direction::east, VehicleType::truck, Turn::right);
    }else{
			lanes.new_vehicle(Direction::east, VehicleType::truck, Turn::straight);
    }
  }

  //WEST
  if(rand < west_truck_s){
    if(rand < west_car_l){
			lanes.new_vehicle(Direction::west, VehicleType::car, Turn::left);
    }else if(rand < west_car_r){
			lanes.new_vehicle(Direction::west, VehicleType::car, Turn::right);
    }else if(rand < west_car_s){
			lanes.new_vehicle(Direction::west, VehicleType::car, Turn::straight);
    }else if(rand < west_SUV_l){
			lanes.new_vehicle(Direction::west, VehicleType::suv, Turn::left);
    }else if(rand < west_SUV_r){
			lanes.new_vehicle(Direction::west, VehicleType::suv, Turn::right);
    }else if(rand < west_SUV_s){
			lanes.new_vehicle(Direction::west, VehicleType::suv, Turn::straight);
    }else if(rand < west_truck_l){
			lanes.new_vehicle(Direction::west, VehicleType::truck, Turn::left);
    }else if(rand < west_truck_r){
			lanes.new_vehicle(Direction::west, VehicleType::truck, Turn::right);
    }else{
			lanes.new_vehicle(Direction::west, VehicleType::truck, Turn::straight);
    }
  }

  //NORTH
  if(rand < north_truck_s){
    if(rand < north_car_l){
			lanes.new_vehicle(Direction::north, VehicleType::car, Turn::left);
    }else if(rand < north_car_r){
			lanes.new_vehicle(Direction::north, VehicleType::car, Turn::right);
    }else if(rand < north_car_s){
			lanes.new_vehicle(Direction::north, VehicleType::car, Turn::straight);
    }else if(rand < north_SUV_l){
			lanes.new_vehicle(Direction::north, VehicleType::suv, Turn::left);
    }else if(rand < north_SUV_r){
			lanes.new_vehicle(Direction::north, VehicleType::suv, Turn::right);
    }else if(rand < north_SUV_s){
			lanes.new_vehicle(Direction::north, VehicleType::suv, Turn::straight);
    }else if(rand < north_truck_l){
			lanes.new_vehicle(Direction::north, VehicleType::truck, Turn::left);
    }else if(rand < north_truck_r){
			lanes.new_vehicle(Direction::north, VehicleType::truck, Turn::right);
    }else{
			lanes.new_vehicle(Direction::north, VehicleType::truck, Turn::straight);
    }
  }

  //SOUTH
  if(rand < south_truck_s){
    if(rand < south_car_l){
			lanes.new_vehicle(Direction::south, VehicleType::car, Turn::left);
    }else if(rand < south_car_r){
			lanes.new_vehicle(Direction::south, VehicleType::car, Turn::right);
    }else if(rand < south_car_s){
			lanes.new_vehicle(Direction::south, VehicleType::car, Turn::straight);
    }else if(rand < south_SUV_l){
			lanes.new_vehicle(Direction::south, VehicleType::suv, Turn::left);
    }else if(rand < south_SUV_r){
			lanes.new_vehicle(Direction::south, VehicleType::suv, Turn::right);
    }else if(rand < south_SUV_s){
			lanes.new_vehicle(Direction::south, VehicleType::suv, Turn::straight);
    }else if(rand < south_truck_l){
			lanes.new_vehicle(Direction::south, VehicleType::truck, Turn::left);
    }else if(rand < south_truck_r){
			lanes.new_vehicle(Direction::south, VehicleType::truck, Turn::right);
    }else{
			lanes.new_vehicle(Direction::south, VehicleType::truck, Turn::straight);
    }
  }


}

void Driver::run(int seed){

  //Animator to draw simulation
  Animator anim(this->number_of_sections_before_intersection);
	Lanes    lanes(this->number_of_sections_before_intersection);

  //random number generation
  mt19937 randomNumberGenerator;
  uniform_real_distribution<double> rand_double(0.0, 1.0);
	randomNumberGenerator.seed(seed);
  double rand;

  int clock = 0;

	boolean ns_red = false;
	boolean ew_red = true;

	int count_ns = 0;
	int count_ew = 0;

  //main loop for the simulation
  while(clock < maximum_simulated_time){
		if(!ns_red){
			count_ns++;
		}


    rand = rand_double(randomNumberGenerator);

    generateVehicles(rand, lanes);

		lanes.progress_lanes(ns_red, ew_red);
    /*
    For each clock tick:
      1) generate a new random number
      2) generate new vehicles and add them to the lanes using generateVehicles()
      3) advance lanes when possible
         - handle turns and straights
      4) imcrement traffic lights towards changes
      5) anim.draw()
      6) wait for input (key click), then loop
    */

    //iterate clock
    clock++;
  }

}

int main(int argc, char* argv[]){

  return 0;
}
