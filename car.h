#include "VehicleBase.h"

class car : public VehicleBase{

  public:
    int sections_before_intersection; //this will have to be set in driver once input is given.

    car(VehicleType car, Direction originalDirection, Turn turn);
    car(const car& other);

    car& operator=(const car& other);

    ~car();


};
