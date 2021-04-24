#ifndef __VB_FACTORY_H__
#define __VB_FACTORY_H__

#include "VehicleBase.h"
#include <random>
#include <vector>
#include <iostream>

using namespace std;

struct VBShell{
	VehicleType type;
	Direction og_direction;
	Turn turn;
};

class VBFactory{
private:
	mt19937 randomNumberGenerator;


	// tokens in order
	vector<double> new_probs; // nb, sb, eb, wb
	double  proportion_of_cars,
					proportion_of_SUVs,
					proportion_of_trucks,
					proportion_right_turn_cars,
					proportion_left_turn_cars,
					proportion_right_turn_SUVs,
					proportion_left_turn_SUVs,
					proportion_right_turn_trucks,
					proportion_left_turn_trucks;

public:
	VBFactory(int seed, vector<double> tokens);

	~VBFactory();

	vector<VBShell> generate_new_vehicles();

};

#endif
