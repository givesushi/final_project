#include "Driver.h"
#include "Counter.h"


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
}

Driver::~Driver(){}

void Driver::generateVehicles(double rand, Counter& counter){ //, Animator anim){

  //values for generating new vehicles each clock tick
  //EAST
  double east_car = this->prob_new_vehicle_eastbound * this->proportion_of_cars;
  double east_car_l = east_car * this->proportion_left_turn_cars;
  double east_car_r = east_car_l + (east_car * this->proportion_right_turn_cars);
  double east_car_s = east_car_r + (east_car * this->proportion_straight_cars);

  double east_SUV = (this->prob_new_vehicle_eastbound * this->proportion_of_SUVs);
  double east_SUV_l = east_car_s + (east_SUV * this->proportion_left_turn_SUVs);
  double east_SUV_r = east_SUV_l + (east_SUV * this->proportion_right_turn_SUVs);
  double east_SUV_s = east_SUV_r + (east_SUV * this->proportion_straight_SUVs);

  double east_truck = (this->prob_new_vehicle_eastbound * this->proportion_of_trucks);
  double east_truck_l = east_SUV_s + (east_truck * this->proportion_left_turn_trucks);
  double east_truck_r = east_truck_l + (east_truck * this->proportion_right_turn_trucks);
  double east_truck_s = east_truck_r + (east_truck * this->proportion_straight_trucks);

  //WEST
  double west_car = this->prob_new_vehicle_westbound * this->proportion_of_cars;
  double west_car_l = west_car * this->proportion_left_turn_cars;
  double west_car_r = west_car_l + (west_car * this->proportion_right_turn_cars);
  double west_car_s = west_car_r + (west_car * this->proportion_straight_cars);

  double west_SUV = (this->prob_new_vehicle_westbound * this->proportion_of_SUVs);
  double west_SUV_l = west_car_s + (west_SUV * this->proportion_left_turn_SUVs);
  double west_SUV_r = west_SUV_l + (west_SUV * this->proportion_right_turn_SUVs);
  double west_SUV_s = west_SUV_r + (west_SUV * this->proportion_straight_SUVs);

  double west_truck = (this->prob_new_vehicle_westbound * this->proportion_of_trucks);
  double west_truck_l = west_SUV_s + (west_truck * this->proportion_left_turn_trucks);
  double west_truck_r = west_truck_l + (west_truck * this->proportion_right_turn_trucks);
  double west_truck_s = west_truck_r + (west_truck * this->proportion_straight_trucks);

  //SOUTH
  double south_car = this->prob_new_vehicle_southbound * this->proportion_of_cars;
  double south_car_l = south_car * this->proportion_left_turn_cars;
  double south_car_r = south_car_l + (south_car * this->proportion_right_turn_cars);
  double south_car_s = south_car_r + (south_car * this->proportion_straight_cars);

  double south_SUV = (this->prob_new_vehicle_southbound * this->proportion_of_SUVs);
  double south_SUV_l = south_car_s + (south_SUV * this->proportion_left_turn_SUVs);
  double south_SUV_r = south_SUV_l + (south_SUV * this->proportion_right_turn_SUVs);
  double south_SUV_s = south_SUV_r + (south_SUV * this->proportion_straight_SUVs);

  double south_truck = (this->prob_new_vehicle_southbound * this->proportion_of_trucks);
  double south_truck_l = south_SUV_s + (south_truck * this->proportion_left_turn_trucks);
  double south_truck_r = south_truck_l + (south_truck * this->proportion_right_turn_trucks);
  double south_truck_s = south_truck_r + (south_truck * this->proportion_straight_trucks);

  //NORTH
  double north_car = this->prob_new_vehicle_northbound * this->proportion_of_cars;
  double north_car_l = north_car * this->proportion_left_turn_cars;
  double north_car_r = north_car_l + (north_car * this->proportion_right_turn_cars);
  double north_car_s = north_car_r + (north_car * this->proportion_straight_cars);

  double north_SUV = (this->prob_new_vehicle_northbound * this->proportion_of_SUVs);
  double north_SUV_l = north_car_s + (north_SUV * this->proportion_left_turn_SUVs);
  double north_SUV_r = north_SUV_l + (north_SUV * this->proportion_right_turn_SUVs);
  double north_SUV_s = north_SUV_r + (north_SUV * this->proportion_straight_SUVs);

  double north_truck = (this->prob_new_vehicle_northbound * this->proportion_of_trucks);
  double north_truck_l = north_SUV_s + (north_truck * this->proportion_left_turn_trucks);
  double north_truck_r = north_truck_l + (north_truck * this->proportion_right_turn_trucks);
  double north_truck_s = north_truck_r + (north_truck * this->proportion_straight_trucks);

  //Generate a new vehicle based on random number for each lane.
  //EAST
  if(rand < east_truck_s){
		total_vehicles++;
		total_eb++;
    if(rand < east_car_l){
      //to do: write in constructors and add to lanes.
			counter.count(Direction::east, VehicleType::car,Turn::left );
			// std::cout << "East Car L" << std::endl;
    }else if(rand < east_car_r){
			counter.count(Direction::east, VehicleType::car,Turn::right);
			// std::cout << "East Car R" << std::endl;
    }else if(rand < east_car_s){
			counter.count(Direction::east, VehicleType::car,Turn::straight );
			// std::cout << "East Car S" << std::endl;
    }else if(rand < east_SUV_l){
			counter.count(Direction::east, VehicleType::suv,Turn::left );
			// std::cout << "East SUV L" << std::endl;
    }else if(rand < east_SUV_r){
			counter.count(Direction::east, VehicleType::suv,Turn::right );
			// std::cout << "East SUV R" << std::endl;
    }else if(rand < east_SUV_s){
			counter.count(Direction::east, VehicleType::suv,Turn::straight );
			// std::cout << "East SUV S" << std::endl;
    }else if(rand < east_truck_l){
			counter.count(Direction::east, VehicleType::truck,Turn::left );
			// std::cout << "East Truck L" << std::endl;
    }else if(rand < east_truck_r){
			counter.count(Direction::east, VehicleType::truck,Turn::right );
			// std::cout << "East Truck R" << std::endl;
    }else{
			counter.count(Direction::east, VehicleType::truck,Turn::straight );
			// std::cout << "East Truck S" << std::endl;
    }
  }

  //WEST
  if(rand < west_truck_s){
		total_vehicles++;
		total_wb++;
    if(rand < west_car_l){
			counter.count(Direction::west, VehicleType::car,Turn::left );
			// std::cout << "West Car L" << std::endl;
    }else if(rand < west_car_r){
			counter.count(Direction::west, VehicleType::car,Turn::right );
			// std::cout << "West Car R" << std::endl;
    }else if(rand < west_car_s){
			counter.count(Direction::west, VehicleType::car,Turn::straight);
			// std::cout << "West Car S" << std::endl;
    }else if(rand < west_SUV_l){
			counter.count(Direction::west, VehicleType::suv,Turn::left );
			// std::cout << "West SUV L" << std::endl;
    }else if(rand < west_SUV_r){
			counter.count(Direction::west, VehicleType::suv,Turn::right );
			// std::cout << "West SUV R" << std::endl;
    }else if(rand < west_SUV_s){
			counter.count(Direction::west, VehicleType::suv,Turn::straight );
			// std::cout << "West SUV S" << std::endl;
    }else if(rand < west_truck_l){
			counter.count(Direction::west, VehicleType::truck,Turn::left );
			// std::cout << "West Truck L" << std::endl;
    }else if(rand < west_truck_r){
			counter.count(Direction::west, VehicleType::truck,Turn::right );
			// std::cout << "West Truck R" << std::endl;
    }else{
			counter.count(Direction::west, VehicleType::truck,Turn::straight );
			// std::cout << "West Truck S" << std::endl;
    }
  }

  //NORTH
  if(rand < north_truck_s){
		total_vehicles++;
		total_nb++;
    if(rand < north_car_l){
			counter.count(Direction::north, VehicleType::car,Turn::left );
			// std::cout << "North Car L" << std::endl;
    }else if(rand < north_car_r){
			counter.count(Direction::north, VehicleType::car,Turn::right );
			// std::cout << "North Car R" << std::endl;
    }else if(rand < north_car_s){
			counter.count(Direction::north, VehicleType::car,Turn::straight );
			// std::cout << "North Car S" << std::endl;
    }else if(rand < north_SUV_l){
			counter.count(Direction::north, VehicleType::suv,Turn::left );
			// std::cout << "North SUV L" << std::endl;
    }else if(rand < north_SUV_r){
			counter.count(Direction::north, VehicleType::suv,Turn::right );
			// std::cout << "North SUV R" << std::endl;
    }else if(rand < north_SUV_s){
			counter.count(Direction::north, VehicleType::suv,Turn::straight );
			// std::cout << "North SUV S" << std::endl;
    }else if(rand < north_truck_l){
			counter.count(Direction::north, VehicleType::truck,Turn::left );
			// std::cout << "North Truck L" << std::endl;
    }else if(rand < north_truck_r){
			counter.count(Direction::north, VehicleType::truck,Turn::right );
			// std::cout << "North Truck R" << std::endl;
    }else{
			counter.count(Direction::north, VehicleType::truck,Turn::straight );
			// std::cout << "North Truck S" << std::endl;
    }
  }

  //SOUTH
  if(rand < south_truck_s){
		total_vehicles++;
		total_sb++;
    if(rand < south_car_l){
			counter.count(Direction::south, VehicleType::car,Turn::left );
			// std::cout << "South Car L" << std::endl;
    }else if(rand < south_car_r){
			counter.count(Direction::south, VehicleType::car,Turn::right );
			// std::cout << "South Car R" << std::endl;
    }else if(rand < south_car_s){
			counter.count(Direction::south, VehicleType::car,Turn::straight );
			// std::cout << "South Car S" << std::endl;
    }else if(rand < south_SUV_l){
			counter.count(Direction::south, VehicleType::suv,Turn::left );
			// std::cout << "South SUV L" << std::endl;
    }else if(rand < south_SUV_r){
			counter.count(Direction::south, VehicleType::suv,Turn::right );
			// std::cout << "South SUV R" << std::endl;
    }else if(rand < south_SUV_s){
			counter.count(Direction::south, VehicleType::suv,Turn::straight );
			// std::cout << "South SUV S" << std::endl;
    }else if(rand < south_truck_l){
			counter.count(Direction::south, VehicleType::truck,Turn::left );
			// std::cout << "South Truck L" << std::endl;
    }else if(rand < south_truck_r){
			counter.count(Direction::south, VehicleType::truck,Turn::right );
			// std::cout << "South Truck R" << std::endl;
    }else{
			counter.count(Direction::south, VehicleType::truck,Turn::straight );
			// std::cout << "South Truck S" << std::endl;
    }
  }


}

void Driver::generate(uniform_real_distribution<double>& rand, mt19937& randomNumberGenerator, Counter& counter){
	double r = rand(randomNumberGenerator);
	if( r < prob_new_vehicle_northbound){
		Turn t = Turn::straight;
		VehicleType type = VehicleType::truck;
		r = rand(randomNumberGenerator);
		if( r < proportion_of_cars ) { type = VehicleType::car; }
		else if( r < proportion_of_cars + proportion_of_SUVs ) { type = VehicleType::suv; }

		r = rand(randomNumberGenerator);
		switch (type) {
			case VehicleType::car :
				if( r < proportion_right_turn_cars ) { t = Turn::right; }
				else if( r < proportion_right_turn_cars + proportion_left_turn_cars ) { t = Turn::left; }
				break;
			case VehicleType::suv :
				if( r < proportion_right_turn_SUVs ) { t = Turn::right; }
				else if( r < proportion_right_turn_SUVs + proportion_left_turn_SUVs ) { t = Turn::left; }
				break;
			case VehicleType::truck :
				if( r < proportion_right_turn_trucks ) { t = Turn::right; }
				else if( r < proportion_right_turn_trucks + proportion_left_turn_trucks ) { t = Turn::left; }
				break;
		}
		counter.count(Direction::north, type, t);

	}

	r = rand(randomNumberGenerator);
	if( r < prob_new_vehicle_southbound){
		Turn t = Turn::straight;
		VehicleType type = VehicleType::truck;
		r = rand(randomNumberGenerator);
		if( r < proportion_of_cars ) { type = VehicleType::car; }
		else if( r < proportion_of_cars + proportion_of_SUVs ) { type = VehicleType::suv; }

		r = rand(randomNumberGenerator);
		switch (type) {
			case VehicleType::car :
				if( r < proportion_right_turn_cars ) { t = Turn::right; }
				else if( r < proportion_right_turn_cars + proportion_left_turn_cars ) { t = Turn::left; }
				break;
			case VehicleType::suv :
				if( r < proportion_right_turn_SUVs ) { t = Turn::right; }
				else if( r < proportion_right_turn_SUVs + proportion_left_turn_SUVs ) { t = Turn::left; }
				break;
			case VehicleType::truck :
				if( r < proportion_right_turn_trucks ) { t = Turn::right; }
				else if( r < proportion_right_turn_trucks + proportion_left_turn_trucks ) { t = Turn::left; }
				break;
		}
		counter.count(Direction::south, type, t);
	}

  r = rand(randomNumberGenerator);
	if( r < prob_new_vehicle_eastbound){
		Turn t = Turn::straight;
		VehicleType type = VehicleType::truck;
		r = rand(randomNumberGenerator);
		if( r < proportion_of_cars ) { type = VehicleType::car; }
		else if( r < proportion_of_cars + proportion_of_SUVs ) { type = VehicleType::suv; }

		r = rand(randomNumberGenerator);
		switch (type) {
			case VehicleType::car :
				if( r < proportion_right_turn_cars ) { t = Turn::right; }
				else if( r < proportion_right_turn_cars + proportion_left_turn_cars ) { t = Turn::left; }
				break;
			case VehicleType::suv :
				if( r < proportion_right_turn_SUVs ) { t = Turn::right; }
				else if( r < proportion_right_turn_SUVs + proportion_left_turn_SUVs ) { t = Turn::left; }
				break;
			case VehicleType::truck :
				if( r < proportion_right_turn_trucks ) { t = Turn::right; }
				else if( r < proportion_right_turn_trucks + proportion_left_turn_trucks ) { t = Turn::left; }
				break;
		}
		counter.count(Direction::east, type, t);
	}

	r = rand(randomNumberGenerator);
	if( r < prob_new_vehicle_westbound){
		Turn t = Turn::straight;
		VehicleType type = VehicleType::truck;
		r = rand(randomNumberGenerator);
		if( r < proportion_of_cars ) { type = VehicleType::car; }
		else if( r < proportion_of_cars + proportion_of_SUVs ) { type = VehicleType::suv; }

		r = rand(randomNumberGenerator);
		switch (type) {
			case VehicleType::car :
				if( r < proportion_right_turn_cars ) { t = Turn::right; }
				else if( r < proportion_right_turn_cars + proportion_left_turn_cars ) { t = Turn::left; }
				break;
			case VehicleType::suv :
				if( r < proportion_right_turn_SUVs ) { t = Turn::right; }
				else if( r < proportion_right_turn_SUVs + proportion_left_turn_SUVs ) { t = Turn::left; }
				break;
			case VehicleType::truck :
				if( r < proportion_right_turn_trucks ) { t = Turn::right; }
				else if( r < proportion_right_turn_trucks + proportion_left_turn_trucks ) { t = Turn::left; }
				break;
		}
		counter.count(Direction::west, type, t);
	}
}

std::vector<double> Driver::run(int seed){

  //Animator to draw simulation
  //Animator anim(this->number_of_sections_before_intersection);

  //random number generation
  mt19937 randomNumberGenerator;
  uniform_real_distribution<double> rand_double(0.0, 1.0);
	randomNumberGenerator.seed(seed);
  double rand;

  int clock = 0;
	Counter counter;

  //main loop for the simulation
  while(clock < maximum_simulated_time){

    rand = rand_double(randomNumberGenerator);
		// std::cout << "Clock time: " << clock << "  :  Rand: " << rand << std::endl;
    generateVehicles(rand, counter); //, anim);

		// generate(rand_double, randomNumberGenerator, counter);

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

	return counter.stats(maximum_simulated_time);

}

int main(int argc, char* argv[]){
	std::vector<double> totals{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	std::vector<double> temp;
	Driver d("input_file_format.txt");
	for(int i = 100; i < 200; i++){
		temp = d.run(i);
		for(int j = 0; j < 16; j++){
			totals[j] += temp[j];
		}
	}
	std::cout << "prob_new_vehicle_northbound: " << totals[0]/100 << std::endl;
	std::cout << "prob_new_vehicle_southbound: " << totals[1]/100 << std::endl;
	std::cout << "prob_new_vehicle_eastbound: " << totals[2]/100 << std::endl;
	std::cout << "prob_new_vehicle_westbound: " << totals[3]/100 << std::endl;
	std::cout << "proportion_of_cars: " << totals[4]/100 << std::endl;
	std::cout << "proportion_of_SUVs: " << totals[5]/100 << std::endl;
	std::cout << "proportion_of_trucks: " << totals[6]/100 << std::endl;
	std::cout << "proportion_right_turn_cars: " << totals[7]/100 << std::endl;
	std::cout << "proportion_left_turn_cars: " << totals[8]/100 << std::endl;
	std::cout << "proportion_straight_cars: " << totals[9]/100 << std::endl;
	std::cout << "proportion_right_turn_SUVs: " << totals[10]/100 << std::endl;
	std::cout << "proportion_left_turn_SUVs: " << totals[11]/100 << std::endl;
	std::cout << "proportion_straight_SUVs: " << totals[12]/100 << std::endl;
	std::cout << "proportion_right_turn_trucks: " << totals[13]/100 << std::endl;
	std::cout << "proportion_left_turn_trucks: " << totals[14]/100 << std::endl;
	std::cout << "proportion_straight_trucks: " << totals[15]/100 << std::endl;

  return 0;
}
