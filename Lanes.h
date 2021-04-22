#ifndef __LANES_H__
#define __LANES_H__

#include <vector>
#include <iostream>
#include <queue>
#include "VehicleBase.h"
#include "Lanes.h"

using namespace std;

class Lanes{
private:
	vector<VehicleBase*> nb_lane;
	vector<VehicleBase*> sb_lane;
	vector<VehicleBase*> eb_lane;
	vector<VehicleBase*> wb_lane;

	queue<VehicleBase*> nb_q;
	queue<VehicleBase*> sb_q;
	queue<VehicleBase*> eb_q;
	queue<VehicleBase*> wb_q;

	boolean nb_enter_busy;
	boolean sb_enter_busy;
	boolean eb_enter_busy;
	boolean wb_enter_busy;

	int lane_len;
 	int halfSize;

	boolean check_clear_left(Direction check, int vehicle_len);
	boolean check_clear_right(Direction check, int vehicle_len);
	boolean check_clear_next(Direction check, int pos);

	void turn_right(VehicleBase* vb, Direction from);
	void turn_left(VehicleBase* vb, Direction from);

	void update_entering_lanes();

public:
	// Constructors
	Lanes(int numSectionsBeforeIntersection);
	~Lanes();

	void progress_lanes(boolean ns_red, boolean ew_red);
	void new_vehicle(Direction dir, VehicleType type, Turn turn);

	inline vector<VehicleBase*> get_nb_lane() const { return this-> nb_lane; }
	inline vector<VehicleBase*> get_sb_lane() const { return this-> sb_lane; }
	inline vector<VehicleBase*> get_eb_lane() const { return this-> eb_lane; }
	inline vector<VehicleBase*> get_wb_lane() const { return this-> wb_lane; }

};

#endif
