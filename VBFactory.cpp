#include "VBFactory.h"

VBFactory::VBFactory(int seed, vector<double> tokens){
	if(tokens.size() != 12)
		cout << "ERROR: Wrong sized token vector!!" << endl;
	else{
		new_probs.push_back(tokens[0]);
		new_probs.push_back(tokens[1]);
		new_probs.push_back(tokens[2]);
		new_probs.push_back(tokens[3]);
		proportion_of_cars = tokens[4];					// what happens when these proportions
		proportion_of_SUVs = tokens[5];					// are more than 1?
		proportion_of_trucks = 1 - proportion_of_cars - proportion_of_SUVs;
		proportion_right_turn_cars = tokens[6];
		proportion_left_turn_cars = tokens[7];
		proportion_right_turn_SUVs = tokens[8];
		proportion_left_turn_SUVs = tokens[9];
		proportion_right_turn_trucks = tokens[10];
		proportion_left_turn_trucks = tokens[11];
	}

	randomNumberGenerator.seed(seed);
}

VBFactory::~VBFactory(){}

vector<VBShell> VBFactory::generate_new_vehicles(){
	vector<VBShell> out;
	uniform_real_distribution<double> rand_double(0,1);
	double randNum = rand_double(randomNumberGenerator);
	for(int i = 0; i < 4; i++){
		if(randNum < this->new_probs[i]){
			VehicleType type = VehicleType::truck;
			Direction og_direction = static_cast<Direction>(i);
			Turn turn = Turn::straight;
			randNum = rand_double(randomNumberGenerator);
			if(randNum < proportion_of_cars){
				type = VehicleType::car;
				if(randNum < proportion_right_turn_cars*proportion_of_cars)
					turn = Turn::right;
				else if(randNum < (proportion_left_turn_cars + proportion_right_turn_cars)*proportion_of_cars)
					turn = Turn::left;
			}else if(randNum < proportion_of_cars+proportion_of_SUVs){
				type = VehicleType::suv;
				if(randNum < proportion_of_cars+(proportion_of_SUVs*proportion_right_turn_SUVs))
					turn = Turn::right;
				else if(randNum < proportion_of_cars+(proportion_of_SUVs*(proportion_right_turn_SUVs+proportion_left_turn_SUVs)))
					turn = Turn::left;
			}else{
				if(randNum < proportion_of_cars+proportion_of_SUVs+proportion_of_trucks*proportion_right_turn_trucks)
					turn = Turn::right;
				else if(randNum < proportion_of_cars+proportion_of_SUVs+proportion_of_trucks*(proportion_right_turn_trucks + proportion_left_turn_trucks))
					turn = Turn::left;
			}out.push_back(VBShell{type,og_direction,turn});
		}randNum = rand_double(randomNumberGenerator);
	}return out;
}

// int main(){
// 	vector<double> tokens{.25,.1,.15,.15,.6,.3,.4,.1,.3,.05,.2,.02};
// 	VBFactory vbf{100, tokens};
//
// 	for(int i = 0; i < 10; i++){
// 		vector<VBShell> shells = vbf.generate_new_vehicles();
// 		for(auto vbs : shells){
// 			int t = (int) vbs.type, d = (int) vbs.og_direction, tn = (int) vbs.turn;
// 			cout << "type: " << t << " direction: " << d << " Turn: " << tn << endl;
// 		}
// 	}
//
// }
