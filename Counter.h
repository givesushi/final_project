#ifndef __COUNTER_H__
#define __COUNTER_H__

//#include "Driver.h"
#include <iostream>
#include <vector>

enum class Direction   {north, south, east, west};
enum class VehicleType {car, suv, truck};
enum class Turn 			 {straight, right, left};

class Counter{
private:
	double no_total_vehicles = 0;

	double no_nb = 0;
	double no_sb = 0;
	double no_eb = 0;
	double no_wb = 0;

	double no_cars = 0;
	double no_trucks = 0;
	double no_SUVs = 0;

	double left_cars = 0;
	double right_cars = 0;
	double straight_cars = 0;

	double left_SUVs = 0;
	double right_SUVs = 0;
	double straight_SUVs = 0;

	double left_trucks = 0;
	double right_trucks = 0;
	double straight_trucks = 0;

public:
	Counter();
	~Counter();

	void count(Direction d, VehicleType v, Turn t);
	void pstats();
	std::vector<double> stats(int time);

};

#endif
