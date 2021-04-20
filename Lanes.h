#ifndef __LANES_H__
#define __LANES_H__

#include <vector>
#include <iostream>
#include "VehicleBase.h"

enum class Direction   {north, south, east, west};
enum class VehicleType {car, suv, truck};
enum class Turn 			 {straight, right, left};

class Lanes{
private:
	std::vector<VehicleBase*> nb_lane;
	std::vector<VehicleBase*> sb_lane;
	std::vector<VehicleBase*> eb_lane;
	std::vector<VehicleBase*> wb_lane;

	boolean nb_enter_busy;
	boolean sb_enter_busy;
	boolean eb_enter_busy;
	boolean wb_enter_busy;

	int lane_len;
 	int halfSize;

	void move_forward(VehicleBase* vehicle);
	void turn_right(VehicleBase* vehicle);
	void turn_left(VehicleBase* vehicle);

	void check_lanes();
	void check_vehicle(VehicleBase& vehicle);
	void new_vehicle(Direction dir, VehicleType type, Turn turn);

public:
	// Constructors
	Lanes(int numSectionsBeforeIntersection);
	~Lanes();

	void progress();
};

#endif
