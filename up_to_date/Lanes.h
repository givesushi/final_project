#ifndef __LANES_H__
#define __LANES_H__

#include <vector>
#include <iostream>
#include <queue>
#include "VehicleBase.h"
#include <exception>
#include <memory>

using namespace std;

class Lanes{

public:
	vector<shared_ptr<VehicleBase>> nb_lane;
	vector<shared_ptr<VehicleBase>> sb_lane;
	vector<shared_ptr<VehicleBase>> eb_lane;
	vector<shared_ptr<VehicleBase>> wb_lane;

	queue<shared_ptr<VehicleBase>> nb_qq;
	queue<shared_ptr<VehicleBase>> sb_qq;
	queue<shared_ptr<VehicleBase>> eb_qq;
	queue<shared_ptr<VehicleBase>> wb_qq;

	bool nb_enter_busy;
	bool sb_enter_busy;
	bool eb_enter_busy;
	bool wb_enter_busy;

	int lane_len;
 	int halfSize;


	// Constructors
	Lanes(int numSectionsBeforeIntersection);
	~Lanes();

	void progress_lanes(bool ns_red, bool ew_red);
	void new_vehicle(shared_ptr<VehicleBase> vb);
	void advanceTops(bool ns_red, int til_red);
	void advanceBottoms();
	void addFromQ();

	inline vector<shared_ptr<VehicleBase>> get_nb_lane() const { return this-> nb_lane; }
	inline vector<shared_ptr<VehicleBase>> get_sb_lane() const { return this-> sb_lane; }
	inline vector<shared_ptr<VehicleBase>> get_eb_lane() const { return this-> eb_lane; }
	inline vector<shared_ptr<VehicleBase>> get_wb_lane() const { return this-> wb_lane; }

};

#endif
