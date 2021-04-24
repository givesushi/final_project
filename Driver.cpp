#include "Driver.h"

Driver::Driver(int halfSize) : numSectionsBefore(halfSize) {
	ID_VehicleBase_map = {};
	coordinate_ID_map = {};
}

Driver::~Driver(){

}

void Driver::new_vehicle(VehicleType type, Direction originalDirection, Turn turn){
	VehicleBase vb{type, originalDirection, turn};
	auto out = this->ID_VehicleBase_map.try_emplace(vb.getVehicleID(),vb);
	// cout << "Added to ID-VB-map: " << get<1>(out) << endl;
	int direction = (int) originalDirection;
	// cout << "Direction : " << direction << endl;
	pair<int,int> coordinate(0,direction);
	int i = 0;
	while(this->coordinate_ID_map.contains(coordinate)){
		i--;
		coordinate = make_pair(i,direction);
	}
	for(int j = 0; j < 2+((int)type); ){
		this->coordinate_ID_map.try_emplace(coordinate,vb.getVehicleID());
		j++;
		coordinate = make_pair(i-j,direction);
	}
}

pair<int,int> Driver::closed_addition(pair<int,int> v1, pair<int,int> v2){
	int x = (get<0>(v1)+get<0>(v2));
	int y = (get<1>(v1)+get<1>(v2))%4;
	return make_pair(x,y);
}

bool Driver::check_clear(pair<int,int> pos, pair<int,int> vec){
	auto check = closed_addition(pos,vec);
	bool out = !(this->coordinate_ID_map.contains(check));
	cout << "CHECKING POS:" << endl;
	cout << "From: (" << to_string(get<0>(pos)) << "," << to_string(get<1>(pos)) << ")->(" << to_string(get<0>(check)) << "," << to_string(get<1>(check)) << ") check: " << out << endl;
	return out;
}

void Driver::update_pos(pair<int,int> pos, pair<int,int> vec){
	auto new_pos = closed_addition(pos,vec);
	int id = this->coordinate_ID_map.at(pos);
	if(get<0>(new_pos) < numSectionsBefore*2+2){
		this->coordinate_ID_map.try_emplace(new_pos,id);
	} this->coordinate_ID_map.erase(pos);
	cout << "UPDATING POS:" << endl;
	cout << "From: (" << to_string(get<0>(pos)) << "," << to_string(get<1>(pos)) << ")->(" << to_string(get<0>(new_pos)) << "," << to_string(get<1>(new_pos)) << ")"<< endl;
}

void Driver::progress_lanes(bool ns_red){
	auto forward = make_pair(1,0), before_intersection = make_pair(1,1),
								 intersection = make_pair(0,-1), right = make_pair(2,1);
	for(auto it = this->coordinate_ID_map.rbegin(); it != this->coordinate_ID_map.rend(); ++it){
		pair<int,int> pos = it->first;
		int x = get<0>(pos), y = get<1>(pos), id = it->second;
		VehicleBase* vb_ptr = &(this->ID_VehicleBase_map.at(id));
		Turn t = vb_ptr->getVehicleTurn();

		bool turning = vb_ptr->isTurning();
		cout << "------------------------------------------------";
		cout << "VehicleID: " << id << " Turning: " << turning << endl;
		bool clear_forward = check_clear(pos,forward);

		if(x > numSectionsBefore && clear_forward){
			update_pos(pos, forward);
		}else if(x == numSectionsBefore){
			if(turning){
				if(t == Turn::right){
					update_pos(pos,right);
				}else{
					update_pos(pos,forward);
				}
			}else if(check_clear(pos,intersection) && clear_forward){
				update_pos(pos,forward);
			}
		}else if((x == numSectionsBefore-1)&& ((y%2==0)^(ns_red))){  // only green lanes
			if(clear_forward && check_clear(pos,before_intersection)){
				update_pos(pos,forward);
				vb_ptr->start_turn();
			}
		}else if(x == numSectionsBefore-1 && turning){
			update_pos(pos,forward);
		}else if(clear_forward)
			update_pos(pos,forward);
	}
}

vector<VehicleBase*> Driver::ptr_lane(Direction lane){
	vector<VehicleBase*> vb_ptrs;
	vb_ptrs.resize(numSectionsBefore*2+2, nullptr);
	pair<int,int> coordinate_pair;
	int x, y;
	for(auto it = this->coordinate_ID_map.begin(); it != this->coordinate_ID_map.end(); ++it){
		coordinate_pair = it->first;
		x = get<0>(coordinate_pair);
		y = get<1>(coordinate_pair);
		if(x > -1 && x < (numSectionsBefore*2+2) && y == (int)lane)
			vb_ptrs[x] = &(this->ID_VehicleBase_map.at(it->second));
	}return vb_ptrs;
}


// int main(){
// 	Driver d;
//
// }
