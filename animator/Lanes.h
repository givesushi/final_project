#ifndef __LANES_H__
#define __LANES_H__

#include <vector>
#include <iostream>
#include <queue>
#include "VehicleBase.h"
// #include "Lanes.h"
#include <exception>

using namespace std;

class Lanes{
public:
	vector<VehicleBase*> nb_lane;
	vector<VehicleBase*> sb_lane;
	vector<VehicleBase*> eb_lane;
	vector<VehicleBase*> wb_lane;

	// queue<VehicleBase*> nb_q;
	// queue<VehicleBase*> sb_q;
	// queue<VehicleBase*> eb_q;
	// queue<VehicleBase*> wb_q;

	vector<VehicleBase*> nb_q;
	vector<VehicleBase*> sb_q;
	vector<VehicleBase*> eb_q;
	vector<VehicleBase*> wb_q;

	bool nb_enter_busy;
	bool sb_enter_busy;
	bool eb_enter_busy;
	bool wb_enter_busy;

	int lane_len;
 	int halfSize;

	bool check_clear_left(Direction check, int vehicle_len);
	bool check_clear_right(Direction check, int vehicle_len);
	bool check_clear_next(Direction check, int pos);

	void turn_right(VehicleBase* vb, Direction from);
	void turn_left(VehicleBase* vb, Direction from);

	void update_entering_lanes();

	// Constructors
	Lanes(int numSectionsBeforeIntersection);
	~Lanes();

	void progress_lanes(bool ns_red, bool ew_red);
	void new_vehicle(VehicleBase* vb);

	inline vector<VehicleBase*> get_nb_lane() const { return this-> nb_lane; }
	inline vector<VehicleBase*> get_sb_lane() const { return this-> sb_lane; }
	inline vector<VehicleBase*> get_eb_lane() const { return this-> eb_lane; }
	inline vector<VehicleBase*> get_wb_lane() const { return this-> wb_lane; }

};

#endif
