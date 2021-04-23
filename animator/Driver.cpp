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

  VehicleBase vb(VehicleType::car, Direction::east, Turn::left);

  //Generate a new vehicle based on random number for each lane.
  //EAST
  if(rand < east_truck_s){
    if(rand < east_car_l){
      vb = VehicleBase(VehicleType::car, Direction::east, Turn::left);
    }else if(rand < east_car_r){
			vb = VehicleBase(VehicleType::car, Direction::east, Turn::right);
    }else if(rand < east_car_s){
      vb = VehicleBase(VehicleType::car, Direction::east, Turn::straight);
    }else if(rand < east_SUV_l){
			vb = VehicleBase(VehicleType::suv, Direction::east, Turn::left);
    }else if(rand < east_SUV_r){
			vb = VehicleBase(VehicleType::suv, Direction::east, Turn::right);
    }else if(rand < east_SUV_s){
			vb = VehicleBase(VehicleType::suv, Direction::east, Turn::straight);
    }else if(rand < east_truck_l){
			vb = VehicleBase(VehicleType::truck, Direction::east, Turn::left);
    }else if(rand < east_truck_r){
			vb = VehicleBase(VehicleType::truck, Direction::east, Turn::right);
    }else{
			vb = VehicleBase(VehicleType::truck, Direction::east, Turn::straight);
    }
  }

  return vb;

  // //WEST
  // if(rand < west_truck_s){
  //   if(rand < west_car_l){
	// 		lanes.new_vehicle(Direction::west, VehicleType::car, Turn::left);
  //   }else if(rand < west_car_r){
	// 		lanes.new_vehicle(Direction::west, VehicleType::car, Turn::right);
  //   }else if(rand < west_car_s){
	// 		lanes.new_vehicle(Direction::west, VehicleType::car, Turn::straight);
  //   }else if(rand < west_SUV_l){
	// 		lanes.new_vehicle(Direction::west, VehicleType::suv, Turn::left);
  //   }else if(rand < west_SUV_r){
	// 		lanes.new_vehicle(Direction::west, VehicleType::suv, Turn::right);
  //   }else if(rand < west_SUV_s){
	// 		lanes.new_vehicle(Direction::west, VehicleType::suv, Turn::straight);
  //   }else if(rand < west_truck_l){
	// 		lanes.new_vehicle(Direction::west, VehicleType::truck, Turn::left);
  //   }else if(rand < west_truck_r){
	// 		lanes.new_vehicle(Direction::west, VehicleType::truck, Turn::right);
  //   }else{
	// 		lanes.new_vehicle(Direction::west, VehicleType::truck, Turn::straight);
  //   }
  // }
  //
  // //NORTH
  // if(rand < north_truck_s){
  //   if(rand < north_car_l){
	// 		lanes.new_vehicle(Direction::north, VehicleType::car, Turn::left);
  //   }else if(rand < north_car_r){
	// 		lanes.new_vehicle(Direction::north, VehicleType::car, Turn::right);
  //   }else if(rand < north_car_s){
	// 		lanes.new_vehicle(Direction::north, VehicleType::car, Turn::straight);
  //   }else if(rand < north_SUV_l){
	// 		lanes.new_vehicle(Direction::north, VehicleType::suv, Turn::left);
  //   }else if(rand < north_SUV_r){
	// 		lanes.new_vehicle(Direction::north, VehicleType::suv, Turn::right);
  //   }else if(rand < north_SUV_s){
	// 		lanes.new_vehicle(Direction::north, VehicleType::suv, Turn::straight);
  //   }else if(rand < north_truck_l){
	// 		lanes.new_vehicle(Direction::north, VehicleType::truck, Turn::left);
  //   }else if(rand < north_truck_r){
	// 		lanes.new_vehicle(Direction::north, VehicleType::truck, Turn::right);
  //   }else{
	// 		lanes.new_vehicle(Direction::north, VehicleType::truck, Turn::straight);
  //   }
  // }
  //
  // //SOUTH
  // if(rand < south_truck_s){
  //   if(rand < south_car_l){
	// 		lanes.new_vehicle(Direction::south, VehicleType::car, Turn::left);
  //   }else if(rand < south_car_r){
	// 		lanes.new_vehicle(Direction::south, VehicleType::car, Turn::right);
  //   }else if(rand < south_car_s){
	// 		lanes.new_vehicle(Direction::south, VehicleType::car, Turn::straight);
  //   }else if(rand < south_SUV_l){
	// 		lanes.new_vehicle(Direction::south, VehicleType::suv, Turn::left);
  //   }else if(rand < south_SUV_r){
	// 		lanes.new_vehicle(Direction::south, VehicleType::suv, Turn::right);
  //   }else if(rand < south_SUV_s){
	// 		lanes.new_vehicle(Direction::south, VehicleType::suv, Turn::straight);
  //   }else if(rand < south_truck_l){
	// 		lanes.new_vehicle(Direction::south, VehicleType::truck, Turn::left);
  //   }else if(rand < south_truck_r){
	// 		lanes.new_vehicle(Direction::south, VehicleType::truck, Turn::right);
  //   }else{
	// 		lanes.new_vehicle(Direction::south, VehicleType::truck, Turn::straight);
  //   }
  // }

}


int main(int argc, char* argv[]){

  //Driver object to get all the inputs.
	Driver driver{argv[1]};

  //Random number generator variables
  //random number seed given by user.
	// int seed = stoi(argv[2]);

  Animator anim(driver.number_of_sections_before_intersection);
  Lanes lanes(driver.number_of_sections_before_intersection);

  VehicleBase vb_n(VehicleType::car, Direction::north, Turn::right);
  VehicleBase vb_s(VehicleType::car, Direction::south, Turn::straight);
  VehicleBase vb_e(VehicleType::car, Direction::east, Turn::straight);
  VehicleBase vb_w(VehicleType::car, Direction::west, Turn::straight);

  cout << lanes.nb_q.size() << endl;


  lanes.new_vehicle(&vb_n);
  lanes.new_vehicle(&vb_s);
  lanes.new_vehicle(&vb_e);
  lanes.new_vehicle(&vb_w);


  for(int i=0; i < 4; i++){
  cout << lanes.nb_q[i] << endl;
  cout << lanes.sb_q[i] << endl;
  cout << lanes.wb_q[i] << endl;
  cout << lanes.eb_q[i] << endl;
}

  lanes.progress_lanes(false, true);
  lanes.progress_lanes(false, true);
  lanes.progress_lanes(false, true);



  anim.setLightNorthSouth(LightColor::green);
  anim.setLightEastWest(LightColor::red);

  anim.setVehiclesNorthbound(lanes.get_nb_lane());
	anim.setVehiclesWestbound(lanes.get_wb_lane());
	anim.setVehiclesSouthbound(lanes.get_sb_lane());
	anim.setVehiclesEastbound(lanes.get_eb_lane());

  anim.draw(1);


  // mt19937 randomNumberGenerator;
  // uniform_real_distribution<double> rand_double(0.0, 1.0);
	// randomNumberGenerator.seed(seed);
  // double rand;
  //
  // int clock = 0;
  //
  // //traffic light variables
  // bool ns_red = false;
	// bool ew_red = true;
	// int count_ns = 0;
	// int count_ew = 0;
  //
  // //lanes object
  // Lanes lanes{driver.number_of_sections_before_intersection};
  //
  // //Animator object
  // Animator anim{driver.number_of_sections_before_intersection};
  // Animator::MAX_VEHICLE_COUNT = 999;
  //
  // //used for input to progress simulation.
  // char dummy;
  //
  // vector<VehicleBase> v;
  // VehicleBase vb(VehicleType::car, Direction::east, Turn::left);
  //
  // //SIMULATION STARTS HERE
  // //main loop for the simulation
  // while(clock < driver.maximum_simulated_time){
  //
  //   //Set traffic lights
	// 	if(count_ns == 0){ ns_red = false; }
	// 	if(!ns_red){
	// 		if(count_ns == 0){
	// 			anim.setLightNorthSouth(LightColor::green);
	// 		}else if(count_ns == driver.green_north_south){
	// 			anim.setLightNorthSouth(LightColor::yellow);
	// 		}else if(count_ns == driver.green_north_south + driver.yellow_north_south){
	// 			anim.setLightNorthSouth(LightColor::red);
	// 			ns_red = true;
	// 			count_ew = 0;
	// 		} count_ns++;
	// 	}else{
	// 		if(count_ew == 0){
	// 			anim.setLightEastWest(LightColor::green);
	// 			ew_red = false;
	// 		}else if(count_ew == driver.green_east_west){
	// 			anim.setLightEastWest(LightColor::yellow);
	// 		}else if(count_ew == driver.green_east_west + driver.yellow_east_west){
	// 			anim.setLightEastWest(LightColor::red);
	// 			ew_red = true;
	// 			count_ns = 0;
	// 		} count_ew++;
	// 	}
  //
  //   //generate a random number
  //   rand = rand_double(randomNumberGenerator);
  //
  //   //generate vehicles based on rand
  //   vb = driver.generateVehicles(rand);
  //   v.push_back(vb);
  //
  //   lanes.new_vehicle(vb);
  //
  //   //update the lanes by one cycle
	// 	// lanes.progress_lanes(ns_red, ew_red);
  //
  //   //give updated lanes to the animator
	// 	anim.setVehiclesNorthbound(lanes.get_nb_lane());
	// 	anim.setVehiclesWestbound(lanes.get_wb_lane());
	// 	anim.setVehiclesSouthbound(lanes.get_sb_lane());
	// 	anim.setVehiclesEastbound(lanes.get_eb_lane());
  //
  //   //draw the intersection
	// 	anim.draw(clock);
  //
  //   //wait for input
	// 	cin.get(dummy);
  //
  //   //iterate clock and loop
  //   clock++;
  // }
  //

  return 0;
}
