#include "Lanes.h"

Lanes::Lanes(int numSectionsBeforeIntersection){
	nb_enter_busy = false;
	sb_enter_busy = false;
	eb_enter_busy = false;
	wb_enter_busy = false;
	lane_len = numSectionsBeforeIntersection*2 + 2;
	halfSize = numSectionsBeforeIntersection;

	nb_lane(lane_len, nullptr);
	sb_lane(lane_len, nullptr);
	eb_lane(lane_len, nullptr);
	wb_lane(lane_len, nullptr);

}

Lanes::~Lanes(){}

void Lanes::move_forward(VehicleBase* vehicle);

void Lanes::turn_right(VehicleBase* vehicle);

void Lanes::turn_left(VehicleBase* vehicle);

void Lanes::check_lanes();

void Lanes::check_vehicle(VehicleBase& vehicle){
	int v_pos = vehicle.getPosition();


	boolean entering = (v_pos < vehicle.get_len());
	boolean exiting = (v_pos == lane_len - 1);

	switch (vehicle.getDirection()) {
		case Direction::north:
			boolean clear = (nb_lane[v_pos+1] == nullptr || nb_lane[v_pos+1] == vehicle);
			if(clear && entering){
				for(int i = v_pos; i > -1; i--){
					move_forward(nb_lane[i]);
				} entering = (vehicle.getPosition() < vehicle.get_len());
				if(entering){
					nb_lane[0] = VehicleBase(vehicle);
				}else{
					nb_enter_busy = false;
				}
			}else if(clear){
				move_forward(vehicle);
			}else if(exiting)
			break;
		case Direction::south:
			boolean clear = (sb_lane[v_pos+1] == nullptr || sb_lane[v_pos+1] == vehicle);
			break;
		case Direction::east:
			boolean clear = (eb_lane[v_pos+1] == nullptr || eb_lane[v_pos+1] == vehicle);
			break;
		case Direction::west:
			boolean clear = (wb_lane[v_pos+1] == nullptr || wb_lane[v_pos+1] == vehicle);
			break;
	}

	if(clear && entering){
		for(int i = v_pos; i > -1; i--){
			move_forward(vehicle);
		}
		switch (vehicle.getDirection()) {
			case Direction::north:
				nb_lane[0] = VehicleBase(vehicle);
				break;
			case Direction::south:
				sb_lane[0] = VehicleBase(vehicle);
				break;
			case Direction::east:
				eb_lane[0] = VehicleBase(vehicle);
				break;
			case Direction::west:
				wb_lane[0] = VehicleBase(vehicle);
				break;
		}
	}
}

void Lanes::new_vehicle(Direction dir, VehicleType type, Turn turn){
	switch (dir) {
		case Direction::north:
			if(!nb_enter_busy){
				nb_lane[0] = VehicleBase(type, dir, turn);
				nb_enter_busy = true;
			} break;
		case Direction::south:
			if(!sb_enter_busy){
				sb_lane[0] = VehicleBase(type, dir, turn);
				sb_enter_busy = true;
			} break;
		case Direction::east:
			if(!eb_enter_busy){
				eb_lane[0] = VehicleBase(type, dir, turn);
				eb_enter_busy = true;
			} break;
		case Direction::west:
			if(!wb_enter_busy){
				wb_lane[0] = VehicleBase(type, dir, turn);
				wb_enter_busy = true;
			} break;
	}
}
