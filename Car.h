#ifndef __CAR_H__
#define __CAR_H__

#include "VehicleBase.h"
#include "Lanes.h"
#include <stack>
#include <iostream>
#inclide <functional>

using namespace std;

enum class Move { FORWARD, RIGHT, LEFT, ENTER, EXIT };

class Car : public VehicleBase {
private:
	vector<Move> moves;
	//const vector<Move> right_car{ENTER,ENTER};

	function<boolean(boolean,int,int)> forward;
	function<boolean(boolean,int)> right;
	function<boolean(int)> left;
	function<boolean(int)> enter;
	function<boolean(int)> exit;

	function<boolean()> clear_crossing;

	const int V_LEN = 2;
	boolean intersection;
	boolean check_next(int pos);
	void initialize_moves();

public:
	// initialize moves
	Car(Direction d, Turn t);
	~Car();

	boolean progress(boolean red, int t_til_red, int pos);
	void initializeLambdas(vector<VehicleBase>& start, vector<VehicleBase>& cross1,
												 vector<VehicleBase>& cross2, vector<VehicleBase>& cross3 );

}


#endif
