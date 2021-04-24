#ifndef __DRIVER_H__
#define __DRIVER_H__

#include <iostream>
#include <map>
#include <iterator>
#include <vector>
#include <utility>
#include "VehicleBase.h"

using namespace std;

class Driver {
public:
	map<pair<int,int>,int> coordinate_ID_map;
	map<int,VehicleBase>   ID_VehicleBase_map;

	int numSectionsBefore;

	void new_vehicle(VehicleType type, Direction originalDirection, Turn turn);

	bool check_clear(pair<int,int> pos, pair<int,int> vec);

	void update_pos(pair<int,int> pos, pair<int,int> vec);

	pair<int,int> closed_addition(pair<int,int> v1, pair<int,int> v2);
	
	bool coordinate_map_contains(pair<int,int> key);

	Driver(int halfSize);
	~Driver();

	vector<VehicleBase*> ptr_lane(Direction lane);
	void progress_lanes(bool ns_red);

};


#endif
