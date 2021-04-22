#include <functional>
#include <iostream>
#include <stack>
#include <vector>
#include <queue>

using namespace std;

enum class Turns{ LEFT, RIGHT, FORWARD };
void turn_right(int x, int y);
void turn_left(int x, int y);
void go_forward(int x,int y);

int main(){
	// stack<Turns> stack{};
	// stack.push(Turns::LEFT);
	// stack.push(Turns::RIGHT);
	// stack.push(Turns::FORWARD);
	// stack.push(Turns::FORWARD);

	vector<Turns> turnVector;
	queue<Turns> turnQueue;

	turnVector.emplace_back(Turns::LEFT);
	turnVector.emplace_back(Turns::RIGHT);
	turnVector.emplace_back(Turns::FORWARD);
	turnVector.emplace_back(Turns::FORWARD);

	turnQueue.push(Turns::LEFT);
	turnQueue.push(Turns::RIGHT);
	turnQueue.push(Turns::FORWARD);

	int x = 0;
	int y = 0;

	function<void()> right = [x,y](){ turn_right(x,y); };
	function<void()> left = [x,y](){ turn_left(x,y); };
	function<void()> forward = [&x,&y](){ x++; y++; };

	cout << turnQueue.pop() << endl;

	// while (!turnQueue.empty()) {
	// 	auto t = turnQueue.pop();
	// 	switch (t) {
	// 		case Turns::RIGHT:
	// 			right();
	// 			break;
	// 		case Turns::LEFT:
	// 			left();
	// 			break;
	// 		case Turns::FORWARD:
	// 			forward();
	// 			break;
	// 	}
  // }
	// for(Turns t : turnVector){
	// 		switch (t) {
	// 			case Turns::RIGHT:
	// 				right();
	// 				break;
	// 			case Turns::LEFT:
	// 				left();
	// 				break;
	// 			case Turns::FORWARD:
	// 				forward();
	// 				break;
	// 		}
	// }
	cout << "x: " << x << ", y: " << y << endl;
}

void turn_right(int x, int y){
	y++;
}

void turn_left(int x, int y){
	x++;
}

void go_forward(int x, int y){
	x++;
	y++;
}
