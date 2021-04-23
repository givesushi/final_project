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
  east_car = prob_new_vehicle_eastbound * proportion_of_cars;
  east_car_l = east_car * proportion_left_turn_cars;
  east_car_r = east_car_l + (east_car * proportion_right_turn_cars);
  east_car_s = east_car_r + (east_car * proportion_straight_cars);

  east_SUV = (prob_new_vehicle_eastbound * proportion_of_SUVs);
  east_SUV_l = east_car_s + (east_SUV * proportion_left_turn_SUVs);
  east_SUV_r = east_SUV_l + (east_SUV * proportion_right_turn_SUVs);
  east_SUV_s = east_SUV_r + (east_SUV * proportion_straight_SUVs);

  east_truck = (prob_new_vehicle_eastbound * proportion_of_trucks);
  east_truck_l = east_SUV_s + (east_truck * proportion_left_turn_trucks);
  east_truck_r = east_truck_l + (east_truck * proportion_right_turn_trucks);
  east_truck_s = east_truck_r + (east_truck * proportion_straight_trucks);

  //WEST
  west_car = prob_new_vehicle_westbound * proportion_of_cars;
  west_car_l = west_car * proportion_left_turn_cars;
  west_car_r = west_car_l + (west_car * proportion_right_turn_cars);
  west_car_s = west_car_r + (west_car * proportion_straight_cars);

  west_SUV = (prob_new_vehicle_westbound * proportion_of_SUVs);
  west_SUV_l = west_car_s + (west_SUV * proportion_left_turn_SUVs);
  west_SUV_r = west_SUV_l + (west_SUV * proportion_right_turn_SUVs);
  west_SUV_s = west_SUV_r + (west_SUV * proportion_straight_SUVs);

  west_truck = (prob_new_vehicle_westbound * proportion_of_trucks);
  west_truck_l = west_SUV_s + (west_truck * proportion_left_turn_trucks);
  west_truck_r = west_truck_l + (west_truck * proportion_right_turn_trucks);
  west_truck_s = west_truck_r + (west_truck * proportion_straight_trucks);

  //SOUTH
  south_car = prob_new_vehicle_southbound * proportion_of_cars;
  south_car_l = south_car * proportion_left_turn_cars;
  south_car_r = south_car_l + (south_car * proportion_right_turn_cars);
  south_car_s = south_car_r + (south_car * proportion_straight_cars);

  south_SUV = (prob_new_vehicle_southbound * proportion_of_SUVs);
  south_SUV_l = south_car_s + (south_SUV * proportion_left_turn_SUVs);
  south_SUV_r = south_SUV_l + (south_SUV * proportion_right_turn_SUVs);
  south_SUV_s = south_SUV_r + (south_SUV * proportion_straight_SUVs);

  south_truck = (prob_new_vehicle_southbound * proportion_of_trucks);
  south_truck_l = south_SUV_s + (south_truck * proportion_left_turn_trucks);
  south_truck_r = south_truck_l + (south_truck * proportion_right_turn_trucks);
  south_truck_s = south_truck_r + (south_truck * proportion_straight_trucks);

  //NORTH
  north_car = prob_new_vehicle_northbound * proportion_of_cars;
  north_car_l = north_car * proportion_left_turn_cars;
  north_car_r = north_car_l + (north_car * proportion_right_turn_cars);
  north_car_s = north_car_r + (north_car * proportion_straight_cars);

  north_SUV = (prob_new_vehicle_northbound * proportion_of_SUVs);
  north_SUV_l = north_car_s + (north_SUV * proportion_left_turn_SUVs);
  north_SUV_r = north_SUV_l + (north_SUV * proportion_right_turn_SUVs);
  north_SUV_s = north_SUV_r + (north_SUV * proportion_straight_SUVs);

  north_truck = (prob_new_vehicle_northbound * proportion_of_trucks);
  north_truck_l = north_SUV_s + (north_truck * proportion_left_turn_trucks);
  north_truck_r = north_truck_l + (north_truck * proportion_right_turn_trucks);
  north_truck_s = north_truck_r + (north_truck * proportion_straight_trucks);

}

Driver::~Driver(){}

VehicleBase Driver::generateVehicles(double rand){
  //Generate a new vehicle based on random number for each lane.
  //EAST
  if(rand < east_truck_s){
    if(rand < east_car_l){
      return VehicleBase(VehicleType::car, Direction::east, Turn::left);
    }else if(rand < east_car_r){
			return VehicleBase(VehicleType::car, Direction::east, Turn::right);
    }else if(rand < east_car_s){
			return VehicleBase(VehicleType::car, Direction::east, Turn::straight);
    }else if(rand < east_SUV_l){
			return VehicleBase(VehicleType::suv, Direction::east, Turn::left);
    }else if(rand < east_SUV_r){
			return VehicleBase(VehicleType::suv, Direction::east, Turn::right);
    }else if(rand < east_SUV_s){
			return VehicleBase(VehicleType::suv, Direction::east, Turn::straight);
    }else if(rand < east_truck_l){
			return VehicleBase(VehicleType::truck, Direction::east, Turn::left);
    }else if(rand < east_truck_r){
			return VehicleBase(VehicleType::truck, Direction::east, Turn::right);
    }else{
			return VehicleBase(VehicleType::truck, Direction::east, Turn::straight);
    }
  } else{
		return VehicleBase(VehicleType::car, Direction::east, Turn::right);
	}

  //WEST
  // if(rand < west_truck_s){
  //   if(rand < west_car_l){
	// 		return VehicleBase(Direction::west, VehicleType::car, Turn::left);
  //   }else if(rand < west_car_r){
	// 		return VehicleBase(Direction::west, VehicleType::car, Turn::right);
  //   }else if(rand < west_car_s){
	// 		return VehicleBase(Direction::west, VehicleType::car, Turn::straight);
  //   }else if(rand < west_SUV_l){
	// 		return VehicleBase(Direction::west, VehicleType::suv, Turn::left);
  //   }else if(rand < west_SUV_r){
	// 		return VehicleBase(Direction::west, VehicleType::suv, Turn::right);
  //   }else if(rand < west_SUV_s){
	// 		return VehicleBase(Direction::west, VehicleType::suv, Turn::straight);
  //   }else if(rand < west_truck_l){
	// 		return VehicleBase(Direction::west, VehicleType::truck, Turn::left);
  //   }else if(rand < west_truck_r){
	// 		return VehicleBase(Direction::west, VehicleType::truck, Turn::right);
  //   }else{
	// 		return VehicleBase(Direction::west, VehicleType::truck, Turn::straight);
  //   }
  // }
	//
  // //NORTH
  // if(rand < north_truck_s){
  //   if(rand < north_car_l){
	// 		return VehicleBase(Direction::north, VehicleType::car, Turn::left);
  //   }else if(rand < north_car_r){
	// 		return VehicleBase(Direction::north, VehicleType::car, Turn::right);
  //   }else if(rand < north_car_s){
	// 		return VehicleBase(Direction::north, VehicleType::car, Turn::straight);
  //   }else if(rand < north_SUV_l){
	// 		return VehicleBase(Direction::north, VehicleType::suv, Turn::left);
  //   }else if(rand < north_SUV_r){
	// 		return VehicleBase(Direction::north, VehicleType::suv, Turn::right);
  //   }else if(rand < north_SUV_s){
	// 		return VehicleBase(Direction::north, VehicleType::suv, Turn::straight);
  //   }else if(rand < north_truck_l){
	// 		return VehicleBase(Direction::north, VehicleType::truck, Turn::left);
  //   }else if(rand < north_truck_r){
	// 		return VehicleBase(Direction::north, VehicleType::truck, Turn::right);
  //   }else{
	// 		return VehicleBase(Direction::north, VehicleType::truck, Turn::straight);
  //   }
  // }
	//
  // //SOUTH
  // if(rand < south_truck_s){
  //   if(rand < south_car_l){
	// 		return VehicleBase(Direction::south, VehicleType::car, Turn::left);
  //   }else if(rand < south_car_r){
	// 		return VehicleBase(Direction::south, VehicleType::car, Turn::right);
  //   }else if(rand < south_car_s){
	// 		return VehicleBase(Direction::south, VehicleType::car, Turn::straight);
  //   }else if(rand < south_SUV_l){
	// 		return VehicleBase(Direction::south, VehicleType::suv, Turn::left);
  //   }else if(rand < south_SUV_r){
	// 		return VehicleBase(Direction::south, VehicleType::suv, Turn::right);
  //   }else if(rand < south_SUV_s){
	// 		return VehicleBase(Direction::south, VehicleType::suv, Turn::straight);
  //   }else if(rand < south_truck_l){
	// 		return VehicleBase(Direction::south, VehicleType::truck, Turn::left);
  //   }else if(rand < south_truck_r){
	// 		return VehicleBase(Direction::south, VehicleType::truck, Turn::right);
  //   }else{
	// 		return VehicleBase(Direction::south, VehicleType::truck, Turn::straight);
  //   }
  // }


}

// void Driver::run(int seed){
//
//   //Animator to draw simulation
// 	Animator::MAX_VEHICLE_COUNT = 999;
//   Animator anim{this->number_of_sections_before_intersection};
// 	Lanes    lanes{this->number_of_sections_before_intersection};
//
//   //random number generation
//   mt19937 randomNumberGenerator;
//   uniform_real_distribution<double> rand_double(0.0, 1.0);
// 	randomNumberGenerator.seed(seed);
//   double rand;
//
//   int clock = 0;
//
// 	bool ns_red = false;
// 	bool ew_red = true;
//
// 	int count_ns = 0;
// 	int count_ew = 0;
//
// 	char dummy;
//   //main loop for the simulation
//   while(clock < maximum_simulated_time){
//
// 		if(count_ns == 0){ ns_red = false; }
// 		if(!ns_red){
// 			if(count_ns == 0){
// 				anim.setLightNorthSouth(LightColor::green);
// 			}else if(count_ns == green_north_south){
// 				anim.setLightNorthSouth(LightColor::yellow);
// 			}else if(count_ns == green_north_south + yellow_north_south){
// 				anim.setLightNorthSouth(LightColor::red);
// 				ns_red = true;
// 				count_ew = 0;
// 			} count_ns++;
// 		}else{
// 			if(count_ew == 0){
// 				anim.setLightEastWest(LightColor::green);
// 				ew_red = false;
// 			}else if(count_ew == green_east_west){
// 				anim.setLightEastWest(LightColor::yellow);
// 			}else if(count_ew == green_east_west + yellow_east_west){
// 				anim.setLightEastWest(LightColor::red);
// 				ew_red = true;
// 				count_ns = 0;
// 			} count_ew++;
// 		}
//
//
//     rand = rand_double(randomNumberGenerator);
//
//     generateVehicles(rand, lanes);
//
// 		lanes.progress_lanes(ns_red, ew_red);
//     /*
//     For each clock tick:
//       1) generate a new random number
//       2) generate new vehicles and add them to the lanes using generateVehicles()
//       3) advance lanes when possible
//          - handle turns and straights
//       4) imcrement traffic lights towards changes
//       5) anim.draw()
//       6) wait for input (key click), then loop
//     */
// 		anim.setVehiclesNorthbound(lanes.get_nb_lane());
// 		anim.setVehiclesWestbound(lanes.get_wb_lane());
// 		anim.setVehiclesSouthbound(lanes.get_sb_lane());
// 		anim.setVehiclesEastbound(lanes.get_eb_lane());
//
// 		anim.draw(clock);
//
// 		cin.get(dummy);
//     //iterate clock
//     clock++;
//   }
//
// }

int main(int argc, char* argv[]){
	Driver driver{argv[1]};

	Animator::MAX_VEHICLE_COUNT = 999;
  Animator anim{driver.return_halfsize()};
	Lanes    lanes{driver.return_halfsize()};

  //random number generation
  mt19937 randomNumberGenerator;
  uniform_real_distribution<double> rand_double(0.0, 1.0);
	randomNumberGenerator.seed(stoi(argv[2]));
  double rand;

  int clock = 0;

	bool ns_red = false;
	bool ew_red = true;

	int count_ns = 0;
	int count_ew = 0;

	int max_t = driver.return_max_time();

	char dummy;
  //main loop for the simulation
  while(clock < max_t){

		if(count_ns == 0){ ns_red = false; }
		if(!ns_red){
			if(count_ns == 0){
				anim.setLightNorthSouth(LightColor::green);
			}else if(count_ns == driver.return_green_north_south()){
				anim.setLightNorthSouth(LightColor::yellow);
			}else if(count_ns == driver.return_green_north_south() + driver.return_yellow_north_south()){
				anim.setLightNorthSouth(LightColor::red);
				ns_red = true;
				count_ew = 0;
			} count_ns++;
		}else{
			if(count_ew == 0){
				anim.setLightEastWest(LightColor::green);
				ew_red = false;
			}else if(count_ew == driver.return_green_east_west()){
				anim.setLightEastWest(LightColor::yellow);
			}else if(count_ew == driver.return_green_east_west() + driver.return_yellow_east_west()){
				anim.setLightEastWest(LightColor::red);
				ew_red = true;
				count_ns = 0;
			} count_ew++;
		}


    rand = rand_double(randomNumberGenerator);

    VehicleBase vb = driver.generateVehicles(rand);
		lanes.assign_vehicle(&vb);


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
		anim.setVehiclesNorthbound(lanes.get_nb_lane());
		anim.setVehiclesWestbound(lanes.get_wb_lane());
		anim.setVehiclesSouthbound(lanes.get_sb_lane());
		anim.setVehiclesEastbound(lanes.get_eb_lane());

		anim.draw(clock);

		cin.get(dummy);
    //iterate clock
    clock++;
  }

  return 0;
}
