#include "Car.h"



Car::Car(Turn t, Direction d) : VehicleBase(VehicleType::car, d, t){
	intersection = false;
	this->initialize_moves();
}

Car::~Car(){}

boolean Car::progress(boolean red, int t_til_red, int pos){
	Move next = moves[0];
	boolean delete;
	switch (next) {
		case Move::FORWARD:
			delete = this->forward(red, t_til_red,pos);
			break;
		case Move::RIGHT:
			delete = this->right(red, t_til_red);
			break;
		case Move::LEFT:
			delete = this->left(pos);
		case Move::ENTER:
			delete = this->enter(pos);
			break;
		case Move::EXIT:
			delete = this->exit(pos);
			break;
	}if(delete){ moves.erase(moves.begin()); }
	return delete;
}

void Car::initialize_moves(){
	Turn t = VehicleBase::getVehicleTurn();
	int lane_len = Lane::lane_len;
	moves{ENTER,ENTER};
	switch (t) {
		case straight:
			for(int i = 0; i < (lane_len-V_LEN)*2; i++){
				moves.emplace_back(FORWARD);
			} break;
		case right:
			for(int i = 0; i < (lane_len/2-1-V_LEN); i++){
				moves.emplace_back(FORWARD);
				moves.emplace_back(FORWARD);
			}moves.emplace_back(RIGHT);
			moves.emplace_back(FORWARD);
			moves.emplace_back(FORWARD);
			moves.emplace_back(RIGHT);
			for(int i = 0; i < (lane_len/2-V_LEN); i++){
				moves.emplace_back(FORWARD);
				moves.emplace_back(FORWARD);
			}break;
		case left:
			for(int i = 0; i < (lane_len/2-V_LEN); i++){
				moves.emplace_back(FORWARD);
				moves.emplace_back(FORWARD);
			}moves.emplace_back(LEFT);
			moves.emplace_back(FORWARD);
			moves.emplace_back(FORWARD);
			moves.emplace_back(LEFT);
			for(int i = 0; i < (lane_len/2-V_LEN); i++){
				moves.emplace_back(FORWARD);
				moves.emplace_back(FORWARD);
			}break;
	}
	moves.emplace_back(EXIT);
	moves.emplace_back(FORWARD);
	moves.emplace_back(EXIT);
}
