#include "car.h"

car::car(VehicleType car, Direction originalDirection, Turn turn) : VehicleBase(car, originalDirection){
  this->turn = turn;
}

//copy constructor
car::car(const car& other) : VehicleBase(other){

  this->turn = other.turn;
  this->sections_before_intersection = other.sections_before_intersection;
}

//copy operator
car& car::operator=(const car& other){
  if(this == &other){
    return *this;
  }

  turn = other.turn;
  vehicleDirection = other.vehicleDirection;
  vehicleType = other.vehicleType;
  vehicleID = other.vehicleID;

  return *this;
}

car::~car(){}

int main(){
  return 0;
}
