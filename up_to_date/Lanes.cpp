#include "Lanes.h"

Lanes::Lanes(int numSectionsBeforeIntersection){

	lane_len = numSectionsBeforeIntersection*2 + 2;
	halfSize = numSectionsBeforeIntersection;

	nb_lane.resize(lane_len, nullptr);
	sb_lane.resize(lane_len, nullptr);
	eb_lane.resize(lane_len, nullptr);
	wb_lane.resize(lane_len, nullptr);

}

Lanes::~Lanes(){
	cout << "Lanes destroyed" << endl;
}

void Lanes::new_vehicle(shared_ptr<VehicleBase> vb){
	if(vb == nullptr)
		return;

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
			if(nb_lane[i+1] == nullptr ){ // || nb_lane[i]->isTurning()){
				nb_lane[i+1] = nb_lane[i];
				nb_lane[i] = nullptr;
			}
		}
		//move up bottoms of south
		if(sb_lane[i] != nullptr ){ // || sb_lane[i]->isTurning()){
			if(sb_lane[i+1] == nullptr){
				sb_lane[i+1] = sb_lane[i];
				sb_lane[i] = nullptr;
			}
		}
		//move up bottoms of east
		if(eb_lane[i] != nullptr ){ // || eb_lane[i]->isTurning()){
			if(eb_lane[i+1] == nullptr){
				eb_lane[i+1] = eb_lane[i];
				eb_lane[i] = nullptr;
			}
		}
		//move up bottoms of west
		if(wb_lane[i] != nullptr ){ // || wb_lane[i]->isTurning()){
			if(wb_lane[i+1] == nullptr){
				wb_lane[i+1] = wb_lane[i];
				wb_lane[i] = nullptr;
			}
		}
	}//for
}//func

void Lanes::advanceTops(bool ns_red, int til_red){
	if(nb_lane[lane_len-1] != nullptr){
		if(nb_lane[lane_len-1] == nb_lane[lane_len-2]){
			nb_lane[lane_len-1] = nullptr;
		}else{
			//delete nb_lane[lane_len-1];
			nb_lane[lane_len-1] = nullptr;
		}
	}
	if(sb_lane[lane_len-1] != nullptr){
		if(sb_lane[lane_len-1] == sb_lane[lane_len-2]){
			sb_lane[lane_len-1] = nullptr;
		}else{
			//delete sb_lane[lane_len-1];
			sb_lane[lane_len-1] = nullptr;
		}
	}
	if(eb_lane[lane_len-1] != nullptr){
		if(eb_lane[lane_len-1] == eb_lane[lane_len-2]){
			eb_lane[lane_len-1] = nullptr;
		}else{
			//delete eb_lane[lane_len-1];
			eb_lane[lane_len-1] = nullptr;
		}
	}
	if(wb_lane[lane_len-1] != nullptr){
		if(wb_lane[lane_len-1] == wb_lane[lane_len-2]){
			wb_lane[lane_len-1] = nullptr;
		}else{
			//delete wb_lane[lane_len-1];
			wb_lane[lane_len-1] = nullptr;
		}
	}


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
		}else if(wb_lane[lane_len/2-1] == nullptr){
			nb_lane[lane_len/2] = nb_lane[lane_len/2-1];
			nb_lane[lane_len/2-1] = nullptr;
		}
	}

		//handle south bound turns
		if(sb_lane[lane_len/2-1] != nullptr){
			if(sb_lane[lane_len/2-1]->getVehicleTurn() == Turn::right){
				wb_lane[lane_len/2+1] = sb_lane[lane_len/2-1];
				sb_lane[lane_len/2-1] = nullptr;
			}else if(eb_lane[lane_len/2-1] == nullptr){
				sb_lane[lane_len/2] = sb_lane[lane_len/2-1];
				sb_lane[lane_len/2-1] = nullptr;
			}
		}

		//handle east bound turns
		if(eb_lane[lane_len/2-1] != nullptr){
			if(eb_lane[lane_len/2-1]->getVehicleTurn() == Turn::right){
				sb_lane[lane_len/2+1] = eb_lane[lane_len/2-1];
				eb_lane[lane_len/2-1] = nullptr;
			}else if(nb_lane[lane_len/2-1] == nullptr){
				eb_lane[lane_len/2] = eb_lane[lane_len/2-1];
				eb_lane[lane_len/2-1] = nullptr;
			}
		}

		//handle west bound turns
		if(wb_lane[lane_len/2-1] != nullptr){
			if(wb_lane[lane_len/2-1]->getVehicleTurn() == Turn::right){
				nb_lane[lane_len/2+1] = wb_lane[lane_len/2-1];
				wb_lane[lane_len/2-1] = nullptr;
			}else if(sb_lane[lane_len/2-1] == nullptr){
				wb_lane[lane_len/2] = wb_lane[lane_len/2-1];
				wb_lane[lane_len/2-1] = nullptr;
			}
		}

		if(nb_lane[lane_len/2-2] != nullptr && eb_lane[lane_len/2] == nullptr){
			if((!ns_red && til_red > nb_lane[lane_len/2-2]->get_len()) || nb_lane[lane_len/2-2]->isTurning()){
				nb_lane[lane_len/2-1] = nb_lane[lane_len/2-2];
				nb_lane[lane_len/2-2] = nullptr;
				nb_lane[lane_len/2-1]->start_turn();
			}
		}

		if(sb_lane[lane_len/2-2] != nullptr && wb_lane[lane_len/2] == nullptr){
			if((!ns_red && til_red > sb_lane[lane_len/2-2]->get_len()) || sb_lane[lane_len/2-2]->isTurning()){
				sb_lane[lane_len/2-1] = sb_lane[lane_len/2-2];
				sb_lane[lane_len/2-2] = nullptr;
				sb_lane[lane_len/2-1]->start_turn();
			}
		}

		if(wb_lane[lane_len/2-2] != nullptr && nb_lane[lane_len/2] == nullptr){
			if((ns_red  && til_red > wb_lane[lane_len/2-2]->get_len()) || wb_lane[lane_len/2-2]->isTurning()){
				wb_lane[lane_len/2-1] = wb_lane[lane_len/2-2];
				wb_lane[lane_len/2-2] = nullptr;
				wb_lane[lane_len/2-1]->start_turn();
			}
		}

		if(eb_lane[lane_len/2-2] != nullptr && sb_lane[lane_len/2] == nullptr){
			if((ns_red  && til_red > eb_lane[lane_len/2-2]->get_len()) || eb_lane[lane_len/2-2]->isTurning()){
				eb_lane[lane_len/2-1] = eb_lane[lane_len/2-2];
				eb_lane[lane_len/2-2] = nullptr;
				eb_lane[lane_len/2-1]->start_turn();
			}
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
