#include "Animator.h"
#include "Driver.h"
#include "VehicleBase.h"
#include "VBFactory.h"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]){
	//check args
	string infile = argv[1];
	int seed = atoi(argv[2]);

	string value;
	int maximum_simulated_time,
			number_of_sections_before_intersection,
			green_north_south,
			yellow_north_south,
			green_east_west,
			yellow_east_west;

	vector<double> random_tokens;
	double stat;

	// get input file parsed
	ifstream input_file{infile};
  if(!input_file){
    cout << "Error: Could not open file:" << infile << endl;
  }else{
		input_file >> value >> maximum_simulated_time;
		input_file >> value >> number_of_sections_before_intersection;
		input_file >> value >> green_north_south;
		input_file >> value >> yellow_north_south;
		input_file >> value >> green_east_west;
		input_file >> value >> yellow_east_west;
		while(input_file >> value >> stat)
			random_tokens.push_back(stat);
	}
	for(auto d : random_tokens)
		cout << d << endl;

	// pass seed and probabilities to Random
	VBFactory vbf{seed, random_tokens};

	// initialize driver and Animator
	Driver d{number_of_sections_before_intersection};
	Animator anim{number_of_sections_before_intersection};

	Animator::MAX_VEHICLE_COUNT = 999;
	char dummy;

	// transition stop lights
	int stoplight_timer = 0, time_ellapsed = 0;
	bool ns_red = false;

	anim.setLightNorthSouth(LightColor::green);
	anim.setLightEastWest(LightColor::red);

	while(time_ellapsed < maximum_simulated_time){ // loop for simulation
		if(ns_red){
			if(stoplight_timer == green_east_west){
				anim.setLightEastWest(LightColor::yellow);
			}else if(stoplight_timer == green_east_west + yellow_east_west){
				anim.setLightEastWest(LightColor::red);
				anim.setLightNorthSouth(LightColor::green);
				ns_red = !ns_red;
				stoplight_timer = 0;
			}
		}else{
			if(stoplight_timer == 0){
				anim.setLightNorthSouth(LightColor::green);
			}else if (stoplight_timer == green_north_south){
				anim.setLightNorthSouth(LightColor::yellow);
			}else if(stoplight_timer == green_north_south + yellow_north_south){
				anim.setLightNorthSouth(LightColor::red);
				anim.setLightEastWest(LightColor::green);
				ns_red = !ns_red;
				stoplight_timer = 0;
			}
		}
		// generate Vehicles
		vector<VBShell> shells = vbf.generate_new_vehicles();

		for(VBShell vbs : shells){
			d.new_vehicle(vbs.type, vbs.og_direction, vbs.turn);
		}

		// run progress lanes
		d.progress_lanes(ns_red);

		// load vehicle pointer vectors
		anim.setVehiclesNorthbound(d.ptr_lane(Direction::north));
		anim.setVehiclesWestbound(d.ptr_lane(Direction::west));
		anim.setVehiclesSouthbound(d.ptr_lane(Direction::south));
		anim.setVehiclesEastbound(d.ptr_lane(Direction::east));

		// animator draw
		anim.draw(time_ellapsed);
		std::cin.get(dummy);

		// increment time
		time_ellapsed++;
		stoplight_timer++;
	}


}
