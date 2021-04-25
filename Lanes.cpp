#include "Lanes.h"

Lanes::Lanes(int numSectionsBeforeIntersection){
	nb_enter_busy = false;
	sb_enter_busy = false;
	eb_enter_busy = false;
	wb_enter_busy = false;

	lane_len = numSectionsBeforeIntersection*2 + 2;
	halfSize = numSectionsBeforeIntersection;

	nb_lane.resize(lane_len, nullptr);
	sb_lane.resize(lane_len, nullptr);
	eb_lane.resize(lane_len, nullptr);
	wb_lane.resize(lane_len, nullptr);

	nb_q.resize(999, nullptr);
	sb_q.resize(999, nullptr);
	eb_q.resize(999, nullptr);
	wb_q.resize(999, nullptr);

}

Lanes::~Lanes(){
	cout << "Lanes destroyed" << endl;
}

bool Lanes::check_clear_left(Direction check, int vehicle_len){
	switch (check) {
		case Direction::north:
			for(int i = 0; i < vehicle_len + 1; i++){
				if(sb_lane[lane_len/2-1-i] != nullptr) { return false; }
			}return true;
		case Direction::south:
			for(int i = 0; i < vehicle_len + 1; i++){
				if(nb_lane[lane_len/2-1-i] != nullptr) { return false; }
			}return true;
		case Direction::east:
			for(int i = 0; i < vehicle_len + 1; i++){
				if(wb_lane[lane_len/2-1-i] != nullptr) { return false; }
			}return true;
		case Direction::west:
			for(int i = 0; i < vehicle_len + 1; i++){
				if(eb_lane[lane_len/2-1-i] != nullptr) { return false; }
			}return true;
	}
}

bool Lanes::check_clear_right(Direction check, int vehicle_len){
	switch (check) {
		case Direction::north:
			for(int i = 0; i < vehicle_len + 1; i++){
				if(eb_lane[lane_len/2-i] != nullptr) { return false; }
			}return true;
		case Direction::south:
			for(int i = 0; i < vehicle_len + 1; i++){
				if(wb_lane[lane_len/2-i] != nullptr) { return false; }
			}return true;
		case Direction::east:
			for(int i = 0; i < vehicle_len + 1; i++){
				if(sb_lane[lane_len/2-i] != nullptr) { return false; }
			}return true;
		case Direction::west:
			for(int i = 0; i < vehicle_len + 1; i++){
				if(nb_lane[lane_len/2-i] != nullptr) { return false; }
			}return true;
	}
}

bool Lanes::check_clear_next(Direction check, int pos){
	bool clear;
	switch (check) {
		case Direction::north:
			clear = (nb_lane[pos+1] == nullptr);
			if(clear){
				if(pos+1 == halfSize){
					return (wb_lane[halfSize+1] == nullptr);
				}else if(pos+1 == halfSize+1){
					return (eb_lane[halfSize] == nullptr);
				}
			} return clear;
		case Direction::south:
			clear = (sb_lane[pos+1] == nullptr);
			if(clear){
				if(pos+1 == halfSize){
					return (eb_lane[halfSize+1] == nullptr);
				}else if(pos+1 == halfSize+1){
					return (wb_lane[halfSize] == nullptr);
				}
			} return clear;
		case Direction::east:
			clear = (eb_lane[pos+1] == nullptr);
			if(clear){
				if(pos+1 == halfSize){
					return (nb_lane[halfSize+1] == nullptr);
				}else if(pos+1 == halfSize+1){
					return (sb_lane[halfSize] == nullptr);
				}
			} return clear;
		case Direction::west:
			clear = (wb_lane[pos+1] == nullptr);
			if(clear){
				if(pos+1 == halfSize){
					return (sb_lane[halfSize+1] == nullptr);
				}else if(pos+1 == halfSize+1){
					return (nb_lane[halfSize] == nullptr);
				}
			} return clear;
	}
}

void Lanes::turn_right(VehicleBase* vb, Direction from){
	switch (from) {
		case Direction::north:
			eb_lane[halfSize+1] = vb;
			nb_lane[halfSize-1] = nullptr;
			break;
		case Direction::south:
			wb_lane[halfSize+1] = vb;
			sb_lane[halfSize-1] = nullptr;
			break;
		case Direction::east:
			sb_lane[halfSize+1] = vb;
			eb_lane[halfSize-1] = nullptr;
			break;
		case Direction::west:
			nb_lane[halfSize+1] = vb;
			wb_lane[halfSize-1] = nullptr;
			break;
	}
}

void Lanes::turn_left(VehicleBase* vb, Direction from){
	switch (from) {
		case Direction::north:
			wb_lane[halfSize+1] = vb;
			nb_lane[halfSize+1] = nullptr;
			break;
		case Direction::south:
			eb_lane[halfSize+1] = vb;
			sb_lane[halfSize+1] = nullptr;
			break;
		case Direction::east:
			nb_lane[halfSize+1] = vb;
			eb_lane[halfSize+1] = nullptr;
			break;
		case Direction::west:
			sb_lane[halfSize+1] = vb;
			wb_lane[halfSize+1] = nullptr;
			break;
	}
}

void Lanes::update_entering_lanes(){
	nb_enter_busy = !(nb_lane[0] == nullptr);
	sb_enter_busy = !(sb_lane[0] == nullptr);
	eb_enter_busy = !(eb_lane[0] == nullptr);
	wb_enter_busy = !(wb_lane[0] == nullptr);

		// if(!nb_enter_busy && !nb_q.empty()){ nb_lane[0] = nb_q.pop(); }
		// if(!sb_enter_busy && !sb_q.empty()){ sb_lane[0] = sb_q.pop(); }
		// if(!eb_enter_busy && !eb_q.empty()){ eb_lane[0] = eb_q.pop(); }
		// if(!wb_enter_busy && !wb_q.empty()){ wb_lane[0] = wb_q.pop(); }

		if(!nb_enter_busy && !nb_q.empty()){
			nb_lane[0] = nb_q[0];
		 	auto it = nb_q.erase(nb_q.begin());
		} if(!sb_enter_busy && !sb_q.empty()){
			sb_lane[0] = sb_q[0];
			auto it = sb_q.erase(nb_q.begin());
		} if(!eb_enter_busy && !eb_q.empty()){
			eb_lane[0] = eb_q[0];
			auto it = eb_q.erase(nb_q.begin());
		} if(!wb_enter_busy && !wb_q.empty()){
			wb_lane[0] = wb_q[0];
			auto it = wb_q.erase(nb_q.begin());
		}
}

void Lanes::progress_lanes(bool ns_red, bool ew_red){
	int pos = this->lane_len-1;
	nb_lane[pos] = nullptr;
	sb_lane[pos] = nullptr;
	eb_lane[pos] = nullptr;
	wb_lane[pos] = nullptr;
	pos--;
	while(pos > this->halfSize+1){
		nb_lane[pos+1] = nb_lane[pos];
		nb_lane[pos] = nullptr;
		sb_lane[pos+1] = sb_lane[pos];
		sb_lane[pos] = nullptr;
		eb_lane[pos+1] = eb_lane[pos];
		eb_lane[pos] = nullptr;
		wb_lane[pos+1] = wb_lane[pos];
		wb_lane[pos] = nullptr;
		pos--;
	} 																		// now at left turn spot
	// left turn spot for nb
	if(nb_lane[pos] != nullptr){
		VehicleBase* vb = nb_lane[pos];
		Direction d = vb->getVehicleOriginalDirection();

		if(d == Direction::north){
			Turn t = vb->getVehicleTurn();
			if(t == Turn::left){
				bool turning = vb->isTurning();
				if(turning || check_clear_left(d,vb->get_len())){
					turn_left(vb,d);
				}else{} //do nothing
			}else{
				nb_lane[pos+1] = vb;
				nb_lane[pos] = nullptr;
			}
		}else{
			nb_lane[pos+1] = vb;
			nb_lane[pos] = nullptr;
		}
	}
	// left turn spot for sb
	if(sb_lane[pos] != nullptr){
		VehicleBase* vb = sb_lane[pos];
		Direction d = vb->getVehicleOriginalDirection();

		if(d == Direction::south){
			Turn t = vb->getVehicleTurn();
			if(t == Turn::left){
				bool turning = vb->isTurning();
				if(turning || check_clear_left(d,vb->get_len())){
					turn_left(vb,d);
				}else{} //do nothing
			}else{
				sb_lane[pos+1] = vb;
				sb_lane[pos] = nullptr;
			}
		}else{
			sb_lane[pos+1] = vb;
			sb_lane[pos] = nullptr;
		}
	}
	// left turn spot for eb
	if(eb_lane[pos] != nullptr){
		VehicleBase* vb = eb_lane[pos];
		Direction d = vb->getVehicleOriginalDirection();

		if(d == Direction::east){
			Turn t = vb->getVehicleTurn();
			if(t == Turn::left){
				bool turning = vb->isTurning();
				if(turning || check_clear_left(d,vb->get_len())){
					turn_left(vb,d);
				}else{} //do nothing
			}else{
				eb_lane[pos+1] = vb;
				eb_lane[pos] = nullptr;
			}
		}else{
			eb_lane[pos+1] = vb;
			eb_lane[pos] = nullptr;
		}
	}

	// left turn spot for wb
	if(wb_lane[pos] != nullptr){
		VehicleBase* vb = wb_lane[pos];
		Direction d = vb->getVehicleOriginalDirection();

		if(d == Direction::west){
			Turn t = vb->getVehicleTurn();
			if(t == Turn::left){
				bool turning = vb->isTurning();
				if(turning || check_clear_left(d,vb->get_len())){
					turn_left(vb,d);
				}else{} //do nothing
			}else{
				wb_lane[pos+1] = vb;
				wb_lane[pos] = nullptr;
			}
		}else{
			wb_lane[pos+1] = vb;
			wb_lane[pos] = nullptr;
		}
	}

	pos--;

	if( nb_lane[pos] != nullptr ){
		if(check_clear_next(Direction::north, pos)){
			nb_lane[pos+1] = nb_lane[pos];
			nb_lane[pos] = nullptr;
		}
	}
	if( sb_lane[pos] != nullptr ){
		if(check_clear_next(Direction::south, pos)){
			sb_lane[pos+1] = nb_lane[pos];
			sb_lane[pos] = nullptr;
		}
	}
	if( eb_lane[pos] != nullptr ){
		if(check_clear_next(Direction::east, pos)){
			eb_lane[pos+1] = nb_lane[pos];
			eb_lane[pos] = nullptr;
		}
	}
	if( wb_lane[pos] != nullptr ){
		if(check_clear_next(Direction::west, pos)){
			wb_lane[pos+1] = nb_lane[pos];
			wb_lane[pos] = nullptr;
		}
	}

	pos--; // now at right turn check

	if(nb_lane[pos] != nullptr){
		VehicleBase* vb = nb_lane[pos];
		Direction d = vb->getVehicleOriginalDirection();
		bool turning = vb->isTurning();
		bool clear = check_clear_next(Direction::north, pos);
		Turn t = vb->getVehicleTurn();
		if(t == Turn::right){
			if(turning){
				turn_right(vb, d);
			}else if(ns_red && check_clear_right(Direction::north, vb->get_len())){
				turn_right(vb, d);
			}else if(!ns_red && clear){
				turn_right(vb, d);
			} // do nothing if not
		}else if(turning){ // already in the intersection/turning ignores light
				nb_lane[pos+1] = nb_lane[pos];
				nb_lane[pos] = nullptr;
		}else if(!ns_red && clear){
			nb_lane[pos+1] = nb_lane[pos];
			nb_lane[pos] = nullptr;
			if(t == Turn::straight){
				vb->start_turn();
			}
		}
	}
	// sb right turn check
	if(sb_lane[pos] != nullptr){
		VehicleBase* vb = sb_lane[pos];
		Direction d = vb->getVehicleOriginalDirection();
		bool turning = vb->isTurning();
		bool clear = check_clear_next(Direction::south, pos);
		Turn t = vb->getVehicleTurn();
		if(t == Turn::right){
			if(turning){
				turn_right(vb, d);
			}else if(ns_red && check_clear_right(Direction::south, vb->get_len())){
				turn_right(vb, d);
			}else if(!ns_red && clear){
				turn_right(vb, d);
			} // do nothing if not
		}else if(turning){ // already in the intersection/turning ignores light
				sb_lane[pos+1] = sb_lane[pos];
				sb_lane[pos] = nullptr;
		}else if(!ns_red && clear){
			sb_lane[pos+1] = sb_lane[pos];
			sb_lane[pos] = nullptr;
			if(t == Turn::straight){
				vb->start_turn();
			}
		}
	}
	// eb right turn check
	if(eb_lane[pos] != nullptr){
		VehicleBase* vb = eb_lane[pos];
		Direction d = vb->getVehicleOriginalDirection();
		bool turning = vb->isTurning();
		bool clear = check_clear_next(Direction::east, pos);
		Turn t = vb->getVehicleTurn();
		if(t == Turn::right){
			if(turning){
				turn_right(vb, d);
			}else if(ew_red && check_clear_right(Direction::east, vb->get_len())){
				turn_right(vb, d);
			}else if(!ew_red && clear){
				turn_right(vb, d);
			} // do nothing if not
		}else if(turning){ // already in the intersection/turning ignores light
				eb_lane[pos+1] = eb_lane[pos];
				eb_lane[pos] = nullptr;
		}else if(!ew_red && clear){
			eb_lane[pos+1] = eb_lane[pos];
			eb_lane[pos] = nullptr;
			if(t == Turn::straight){
				vb->start_turn();
			}
		}
	}
	// wb right turn check
	if(wb_lane[pos] != nullptr){
		VehicleBase* vb = wb_lane[pos];
		Direction d = vb->getVehicleOriginalDirection();
		bool turning = vb->isTurning();
		bool clear = check_clear_next(Direction::west, pos);
		Turn t = vb->getVehicleTurn();
		if(t == Turn::right){
			if(turning){
				turn_right(vb, d);
			}else if(ew_red && check_clear_right(Direction::west, vb->get_len())){
				turn_right(vb, d);
			}else if(!ew_red && clear){
				turn_right(vb, d);
			} // do nothing if not
		}else if(turning){ // already in the intersection/turning ignores light
				wb_lane[pos+1] = wb_lane[pos];
				wb_lane[pos] = nullptr;
		}else if(!ew_red && clear){
			wb_lane[pos+1] = wb_lane[pos];
			wb_lane[pos] = nullptr;
			if(t == Turn::straight){
				vb->start_turn();
			}
		}
	}
	pos--;
	// before intersection
	while(pos > -1){
		if(nb_lane[pos] != nullptr){
			if(check_clear_next(Direction::north, pos)){
				nb_lane[pos+1] = nb_lane[pos];
				nb_lane[pos] = nullptr;
			}
		}
		if(sb_lane[pos] != nullptr){
			if(check_clear_next(Direction::south, pos)){
				sb_lane[pos+1] = sb_lane[pos];
				sb_lane[pos] = nullptr;
			}
		}
		if(eb_lane[pos] != nullptr){
			if(check_clear_next(Direction::east, pos)){
				eb_lane[pos+1] = eb_lane[pos];
				eb_lane[pos] = nullptr;
			}
		}
		if(wb_lane[pos] != nullptr){
			if(check_clear_next(Direction::west, pos)){
				wb_lane[pos+1] = wb_lane[pos];
				wb_lane[pos] = nullptr;
			}
		}
		pos--;
	}
	update_entering_lanes();
}


void Lanes::new_vehicle(VehicleBase* vb){

	Direction dir = vb->getVehicleOriginalDirection();
	int len = vb->get_len();

	if(dir == Direction::north){
		for(int i = 0; i < len; i++){
			nb_qq.push(vb);
		}
	}else if(dir == Direction::south){
		for(int i = 0; i < len; i++){
			sb_qq.push(vb);
		}
	}else if(dir == Direction::east){
		for(int i = 0; i < len; i++){
			eb_qq.push(vb);
		}
	}else{
		for(int i = 0; i < len; i++){
			wb_qq.push(vb);
		}
	}
}



void Lanes::advanceBottoms(){

	for(int i = (lane_len/2)-3; i > -1; i--){

		//move up bottoms of north
		if(nb_lane[i] != nullptr){
			if(nb_lane[i+1] == nullptr){
				nb_lane[i+1] = nb_lane[i];
				nb_lane[i] = nullptr;
			}
		}
		//move up bottoms of south
		if(sb_lane[i] != nullptr){
			if(sb_lane[i+1] == nullptr){
				sb_lane[i+1] = sb_lane[i];
				sb_lane[i] = nullptr;
			}
		}
		//move up bottoms of east
		if(eb_lane[i] != nullptr){
			if(eb_lane[i+1] == nullptr){
				eb_lane[i+1] = eb_lane[i];
				eb_lane[i] = nullptr;
			}
		}
		//move up bottoms of west
		if(wb_lane[i] != nullptr){
			if(wb_lane[i+1] == nullptr){
				wb_lane[i+1] = wb_lane[i];
				wb_lane[i] = nullptr;
			}
		}
	}//for
}//func


void Lanes::advanceTops(bool ns_red, bool ew_red){
	nb_lane[lane_len-1] = nullptr;
	sb_lane[lane_len-1] = nullptr;
	eb_lane[lane_len-1] = nullptr;
	wb_lane[lane_len-1] = nullptr;

	for(int i = lane_len-2; i > lane_len/2 -1; i--){
		//move up tops of north
		if(nb_lane[i] != nullptr){
			if(nb_lane[i+1] == nullptr){
				nb_lane[i+1] = nb_lane[i];
				nb_lane[i] = nullptr;
			}
		}

		//move up tops of south
		if(sb_lane[i] != nullptr){
			if(sb_lane[i+1] == nullptr){
				sb_lane[i+1] = sb_lane[i];
				sb_lane[i] = nullptr;
			}
		}
		//move up tops of east
		if(eb_lane[i] != nullptr){
			if(eb_lane[i+1] == nullptr){
				eb_lane[i+1] = eb_lane[i];
				eb_lane[i] = nullptr;
			}
		}
		//move up tops of west
		if(wb_lane[i] != nullptr){
			if(wb_lane[i+1] == nullptr){
				wb_lane[i+1] = wb_lane[i];
				wb_lane[i] = nullptr;
			}
		}
	}//for

	//handle north bound turns
	if(nb_lane[lane_len/2-1] != nullptr){
		if(nb_lane[lane_len/2-1]->getVehicleTurn() == Turn::right){
			eb_lane[lane_len/2+1] = nb_lane[lane_len/2-1];
			nb_lane[lane_len/2-1] = nullptr;
		}else{
			nb_lane[lane_len/2] = nb_lane[lane_len/2-1];
			nb_lane[lane_len/2-1] = nullptr;
		}
	}

	if(!ns_red && nb_lane[lane_len/2-2] != nullptr){
			nb_lane[lane_len/2-1] = nb_lane[lane_len/2-2];
			nb_lane[lane_len/2-2] = nullptr;
		}

		//handle south bound turns
		if(sb_lane[lane_len/2-1] != nullptr){
			if(sb_lane[lane_len/2-1]->getVehicleTurn() == Turn::right){
				wb_lane[lane_len/2+1] = sb_lane[lane_len/2-1];
				sb_lane[lane_len/2-1] = nullptr;
			}else{
				sb_lane[lane_len/2] = sb_lane[lane_len/2-1];
				sb_lane[lane_len/2-1] = nullptr;
			}
		}

		if(!ns_red && sb_lane[lane_len/2-2] != nullptr){
				sb_lane[lane_len/2-1] = sb_lane[lane_len/2-2];
				sb_lane[lane_len/2-2] = nullptr;
			}

		//handle east bound turns
		if(eb_lane[lane_len/2-1] != nullptr){
			if(eb_lane[lane_len/2-1]->getVehicleTurn() == Turn::right){
				sb_lane[lane_len/2+1] = eb_lane[lane_len/2-1];
				eb_lane[lane_len/2-1] = nullptr;
			}else{
				eb_lane[lane_len/2] = eb_lane[lane_len/2-1];
				eb_lane[lane_len/2-1] = nullptr;
			}
		}

		if(!ew_red && eb_lane[lane_len/2-2] != nullptr){
				eb_lane[lane_len/2-1] = eb_lane[lane_len/2-2];
				eb_lane[lane_len/2-2] = nullptr;
			}

		//handle west bound turns
		if(wb_lane[lane_len/2-1] != nullptr){
			if(wb_lane[lane_len/2-1]->getVehicleTurn() == Turn::right){
				nb_lane[lane_len/2+1] = wb_lane[lane_len/2-1];
				wb_lane[lane_len/2-1] = nullptr;
			}else{
				wb_lane[lane_len/2] = wb_lane[lane_len/2-1];
				wb_lane[lane_len/2-1] = nullptr;
			}
		}

		if(!ew_red && wb_lane[lane_len/2-2] != nullptr){
				wb_lane[lane_len/2-1] = wb_lane[lane_len/2-2];
				wb_lane[lane_len/2-2] = nullptr;
			}

}//func



void Lanes::addFromQ(){

	//add from nb queue
	if(!nb_qq.empty()){
		if(nb_lane[0] == nullptr){
			nb_lane[0] = nb_qq.front();
			nb_qq.pop();
		}
	}

	//add from sb queue
	if(!sb_qq.empty()){
		if(sb_lane[0] == nullptr){
			sb_lane[0] = sb_qq.front();
			sb_qq.pop();
		}
	}

	//add from eb queue
	if(!eb_qq.empty()){
		if(eb_lane[0] == nullptr){
			eb_lane[0] = eb_qq.front();
			eb_qq.pop();
		}
	}

	//add from wb queue
	if(!wb_qq.empty()){
		if(wb_lane[0] == nullptr){
			wb_lane[0] = wb_qq.front();
			wb_qq.pop();
		}
	}


}//func
