#define CATCH_CONFIG_MAIN
#include "Lanes.h"
#include "Catch.hpp"

Lanes::Lanes(int numSectionsBeforeIntersection){
	nb_enter_busy = false;
	sb_enter_busy = false;
	eb_enter_busy = false;
	wb_enter_busy = false;
	lane_len = numSectionsBeforeIntersection*2 + 2;
	halfSize = numSectionsBeforeIntersection;

	// nb_lane{lane_len, nullptr};
	// sb_lane{lane_len, nullptr};
	// eb_lane{lane_len, nullptr};
	// wb_lane{lane_len, nullptr};
	//
	// nb_q();
	// sb_q();
	// eb_q();
	// wb_q();

}

Lanes::~Lanes(){}

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

// void Lanes::new_vehicle(Direction dir, VehicleType type, Turn turn){
// 	VehicleBase vb{type, dir, turn};
// 	switch (dir) {
// 		case Direction::north:
// 			for(int i = 0; i < vb.get_len(); i++){
// 				// nb_q.push(&vb);
// 				nb_q.push_back(&vb);
// 			} break;
// 		case Direction::south:
// 			for(int i = 0; i < vb.get_len(); i++){
// 				// sb_q.push(&vb);
// 				sb_q.push_back(&vb);
// 			} break;
// 		case Direction::east:
// 			for(int i = 0; i < vb.get_len(); i++){
// 				// eb_q.push(&vb);
// 				eb_q.push_back(&vb);
// 			} break;
// 		case Direction::west:
// 			for(int i = 0; i < vb.get_len(); i++){
// 				// wb_q.push(&vb);
// 				wb_q.push_back(&vb);
// 			} break;
// 	}
// }

void Lanes::assign_vehicle(VehicleBase* vb){

	switch (vb->getVehicleOriginalDirection()) {
		case Direction::north:
			for(int i = 0; i < vb->get_len(); i++){
				// nb_q.push(&vb);
				nb_q.push_back(vb);
			} break;
		case Direction::south:
			for(int i = 0; i < vb->get_len(); i++){
				// sb_q.push(&vb);
				sb_q.push_back(vb);
			} break;
		case Direction::east:
			for(int i = 0; i < vb->get_len(); i++){
				// eb_q.push(&vb);
				eb_q.push_back(vb);
			} break;
		case Direction::west:
			for(int i = 0; i < vb->get_len(); i++){
				// wb_q.push(&vb);
				wb_q.push_back(vb);
			} break;
	}
}
