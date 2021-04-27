#include "Counter.h"

Counter::Counter(){}

Counter::~Counter(){}

void Counter::count(shared_ptr<VehicleBase> vb_ptr){
	no_total_vehicles++;
	switch (vb_ptr->getVehicleOriginalDirection()) {
		case Direction::north : no_nb++; break;
		case Direction::south : no_sb++; break;
		case Direction::east : no_eb++; break;
		case Direction::west : no_wb++; break;
	}
	switch (vb_ptr->getVehicleType()){
		case VehicleType::car :
			switch (vb_ptr->getVehicleTurn()) {
				case Turn::left : left_cars++; break;
				case Turn::right : right_cars++; break;
				case Turn::straight : straight_cars++; break;
			}no_cars++;
			break;
		case VehicleType::suv :
			switch (vb_ptr->getVehicleTurn()) {
				case Turn::left : left_SUVs++; break;
				case Turn::right : right_SUVs++; break;
				case Turn::straight : straight_SUVs++; break;
			}no_SUVs++;
				break;
		case VehicleType::truck :
			switch (vb_ptr->getVehicleTurn()) {
				case Turn::left : left_trucks++; break;
				case Turn::right : right_trucks++; break;
				case Turn::straight : straight_trucks++; break;
			}no_trucks++;
			break;
	}
}

void Counter::pstats(){
	std::cout << "Total Vehicles: " << no_total_vehicles << std::endl;
	std::cout << "No. NB: " << no_nb << std::endl;
	std::cout << "No. SB: " << no_sb << std::endl;
	std::cout << "No. EB: " << no_eb << std::endl;
	std::cout << "No. WB: " << no_wb << std::endl;

	std::cout << "No. Cars: " << no_cars << std::endl;
	std::cout << "No. SUVs: " << no_SUVs << std::endl;
	std::cout << "No. Trucks: " << no_trucks << std::endl;

	std::cout << "Prop of Cars: " << no_cars/no_total_vehicles << std::endl;
	std::cout << "Prop of SUVs: " << no_SUVs/no_total_vehicles << std::endl;
	std::cout << "Prop of Trucks: " << no_trucks/no_total_vehicles << std::endl;

	std::cout << "Prop right Cars: " << right_cars/no_cars << std::endl;
	std::cout << "Prop left Cars: " << left_cars/no_cars << std::endl;
	std::cout << "Prop straight Cars: " << straight_cars/no_cars << std::endl;

	std::cout << "Prop right SUVs: " << right_SUVs/no_SUVs << std::endl;
	std::cout << "Prop left SUVs: " << left_SUVs/no_SUVs << std::endl;
	std::cout << "Prop straight SUVs: " << straight_SUVs/no_SUVs << std::endl;

	std::cout << "Prop right trucks: " << right_trucks/no_trucks << std::endl;
	std::cout << "Prop left trucks: " << left_trucks/no_trucks << std::endl;
	std::cout << "Prop straight trucks: " << straight_trucks/no_trucks << std::endl;

}

std::vector<double> Counter::stats(int time){
	std::vector<double> out{};
	out.emplace_back(no_nb/((double) time));
	out.emplace_back(no_sb/((double) time));
	out.emplace_back(no_eb/((double) time));
	out.emplace_back(no_wb/((double) time));
	out.emplace_back(no_cars/no_total_vehicles);
	out.emplace_back(no_SUVs/no_total_vehicles);
	out.emplace_back(no_trucks/no_total_vehicles);
	out.emplace_back(right_cars/no_cars);
	out.emplace_back(left_cars/no_cars);
	out.emplace_back(straight_cars/no_cars);
	out.emplace_back(right_SUVs/no_SUVs);
	out.emplace_back(left_SUVs/no_SUVs);
	out.emplace_back(straight_SUVs/no_SUVs);
	out.emplace_back(right_trucks/no_trucks);
	out.emplace_back(left_trucks/no_trucks);
	out.emplace_back(straight_trucks/no_trucks);
	return out;
}
