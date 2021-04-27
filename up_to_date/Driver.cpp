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

shared_ptr<VehicleBase> Driver::generateVehicles(double rand, Direction start){

  //Generate a new vehicle based on random number for each lane.
  //EAST
	switch(start){
		case Direction::east:
			if(rand < east_truck_s){
				if(rand < east_car_l){
					return shared_ptr<VehicleBase>(new VehicleBase(VehicleType::car, Direction::east, Turn::left));
				}else if(rand < east_car_r){
					return shared_ptr<VehicleBase>(new VehicleBase(VehicleType::car, Direction::east, Turn::right));
				}else if(rand < east_car_s){
					return shared_ptr<VehicleBase>(new VehicleBase(VehicleType::car, Direction::east, Turn::straight));
				}else if(rand < east_SUV_l){
					return shared_ptr<VehicleBase>(new VehicleBase(VehicleType::suv, Direction::east, Turn::left));
				}else if(rand < east_SUV_r){
					return shared_ptr<VehicleBase>(new VehicleBase(VehicleType::suv, Direction::east, Turn::right));
				}else if(rand < east_SUV_s){
					return shared_ptr<VehicleBase>(new VehicleBase(VehicleType::suv, Direction::east, Turn::straight));
				}else if(rand < east_truck_l){
					return shared_ptr<VehicleBase>(new VehicleBase(VehicleType::truck, Direction::east, Turn::left));
				}else if(rand < east_truck_r){
					return shared_ptr<VehicleBase>(new VehicleBase(VehicleType::truck, Direction::east, Turn::right));
				}else{
					return shared_ptr<VehicleBase>(new VehicleBase(VehicleType::truck, Direction::east, Turn::straight));
				}
			} return nullptr;
		case Direction::west:
			if(rand < west_truck_s){
				if(rand < west_car_l){
					return shared_ptr<VehicleBase>(new VehicleBase(VehicleType::car, Direction::west, Turn::left));
				}else if(rand < west_car_r){
					return shared_ptr<VehicleBase>(new VehicleBase(VehicleType::car, Direction::west, Turn::right));
				}else if(rand < west_car_s){
					return shared_ptr<VehicleBase>(new VehicleBase(VehicleType::car, Direction::west, Turn::straight));
				}else if(rand < west_SUV_l){
					return shared_ptr<VehicleBase>(new VehicleBase(VehicleType::suv, Direction::west, Turn::left));
				}else if(rand < west_SUV_r){
					return shared_ptr<VehicleBase>(new VehicleBase(VehicleType::suv, Direction::west, Turn::right));
				}else if(rand < west_SUV_s){
					return shared_ptr<VehicleBase>(new VehicleBase(VehicleType::suv, Direction::west, Turn::straight));
				}else if(rand < west_truck_l){
					return shared_ptr<VehicleBase>(new VehicleBase(VehicleType::truck, Direction::west, Turn::left));
				}else if(rand < west_truck_r){
					return shared_ptr<VehicleBase>(new VehicleBase(VehicleType::truck, Direction::west, Turn::right));
				}else{
					return shared_ptr<VehicleBase>(new VehicleBase(VehicleType::truck, Direction::west, Turn::straight));
				}
			}return nullptr;
		case Direction::north:
			if(rand < north_truck_s){
				if(rand < north_car_l){
					return shared_ptr<VehicleBase>(new VehicleBase(VehicleType::car, Direction::north, Turn::left));
				}else if(rand < north_car_r){
					return shared_ptr<VehicleBase>(new VehicleBase(VehicleType::car, Direction::north, Turn::right));
				}else if(rand < north_car_s){
					return shared_ptr<VehicleBase>(new VehicleBase(VehicleType::car, Direction::north, Turn::straight));
				}else if(rand < north_SUV_l){
					return shared_ptr<VehicleBase>(new VehicleBase(VehicleType::suv, Direction::north, Turn::left));
				}else if(rand < north_SUV_r){
					return shared_ptr<VehicleBase>(new VehicleBase(VehicleType::suv, Direction::north, Turn::right));
				}else if(rand < north_SUV_s){
					return shared_ptr<VehicleBase>(new VehicleBase(VehicleType::suv, Direction::north, Turn::straight));
				}else if(rand < north_truck_l){
					return shared_ptr<VehicleBase>(new VehicleBase(VehicleType::truck, Direction::north, Turn::left));
				}else if(rand < north_truck_r){
					return shared_ptr<VehicleBase>(new VehicleBase(VehicleType::truck, Direction::north, Turn::right));
				}else{
					return shared_ptr<VehicleBase>(new VehicleBase(VehicleType::truck, Direction::north, Turn::straight));
				}
			}return nullptr;
		case Direction::south:
			if(rand < south_truck_s){
		    if(rand < south_car_l){
					return shared_ptr<VehicleBase>(new VehicleBase(VehicleType::car, Direction::south, Turn::left));
		    }else if(rand < south_car_r){
					return shared_ptr<VehicleBase>(new VehicleBase(VehicleType::car, Direction::south, Turn::right));
		    }else if(rand < south_car_s){
					return shared_ptr<VehicleBase>(new VehicleBase(VehicleType::car, Direction::south, Turn::straight));
		    }else if(rand < south_SUV_l){
					return shared_ptr<VehicleBase>(new VehicleBase(VehicleType::suv, Direction::south, Turn::left));
		    }else if(rand < south_SUV_r){
					return shared_ptr<VehicleBase>(new VehicleBase(VehicleType::suv, Direction::south, Turn::right));
		    }else if(rand < south_SUV_s){
					return shared_ptr<VehicleBase>(new VehicleBase(VehicleType::suv, Direction::south, Turn::straight));
		    }else if(rand < south_truck_l){
					return shared_ptr<VehicleBase>(new VehicleBase(VehicleType::truck, Direction::south, Turn::left));
		    }else if(rand < south_truck_r){
					return shared_ptr<VehicleBase>(new VehicleBase(VehicleType::truck, Direction::south, Turn::right));
		    }else{
					return shared_ptr<VehicleBase>(new VehicleBase(VehicleType::truck, Direction::south, Turn::straight));
		    }
		  } return nullptr;
		}
}



/*
To randomly generate vehhicles, the program takes the initial seed value and uses it to generate a random double.
Then, it takes probabilities from the input file and uses them to determine the type of each vehicle, its direction,
and which direction it will turn in, if any, using the random double.

For example, taking the following probabilities as input:
prob_new_vehicle_northbound:               0.25
prob_new_vehicle_southbound:               0.1
prob_new_vehicle_eastbound:                0.15
prob_new_vehicle_westbound:                0.15
proportion_of_cars:                        0.6
proportion_of_SUVs:                        0.3
proportion_right_turn_cars:                0.4
proportion_left_turn_cars:                 0.1
proportion_right_turn_SUVs:                0.3
proportion_left_turn_SUVs:                 0.05
proportion_right_turn_trucks:              0.2
proportion_left_turn_trucks:               0.02

We first calculate each percentage and multiply them together. For example:
proportion_of_cars = proportion_of_cars/(proportion_of_cars + proportion_of_SUVs)

Is equivalent to:
proportion_of_cars = 0.6/0.9

We don't do this:
prob_new_vehicle_northbound = 0.25/(0.25+0.1+0.15+0.15) = 0.25/0.65

Because that's a probability, not a proportion. So:
vb10 = prob_new_vehicle_northbound * proportion_of_cars = 0.25(0.6/0.9) (this comes out to about 0.17)

Then we generate a random double. If the value is between 0-0.17, we generate a northbound car. If the value is
between 0.18-0.25, we generate a northbound truck, and so on.
*/
