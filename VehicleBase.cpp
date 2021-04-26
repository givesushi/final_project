#ifndef __VEHICLE_BASE_CPP__
#define __VEHICLE_BASE_CPP__

#include "VehicleBase.h"

int VehicleBase::vehicleCount = 0;

//move constructor
VehicleBase::VehicleBase(VehicleBase&& other) noexcept
    : vehicleID(other.vehicleID),
      vehicleType(other.vehicleType),
      vehicleDirection(other.vehicleDirection),
			vehicleTurn(other.vehicleTurn),
			len(other.len),
			turning(other.turning) {
        other.vehicleID = 0;
        other.vehicleType = static_cast<VehicleType>(999);
        other.vehicleDirection = static_cast<Direction>(999);
        other.vehicleTurn = static_cast<Turn>(999);
        other.turning = false;
				other.len = 0;
				std::cout << "MOVE CONSTRUCTOR " << vehicleID << std::endl;
      }

VehicleBase::VehicleBase(VehicleType type, Direction direction, Turn turn)
    : vehicleID(VehicleBase::vehicleCount++),
      vehicleType(type),
      vehicleDirection(direction),
			vehicleTurn(turn),
			turning(false),
			len(((int)type) + 2)
{}

VehicleBase::VehicleBase(const VehicleBase& other)
    : vehicleID(other.vehicleID),
      vehicleType(other.vehicleType),
      vehicleDirection(other.vehicleDirection),
			vehicleTurn(other.vehicleTurn),
			turning(other.turning),
			len(other.len)
{
	std::cout << "COPY CONSTRUCTOR " << vehicleID << std::endl;
}

	//copy operator
VehicleBase& VehicleBase::operator=(const VehicleBase& other){
	 if(this == &other){
	   return *this;
	 }
	 std::cout << "COPYING " << other.vehicleID << std::endl;

	  vehicleID = other.vehicleID;
	  vehicleType = other.vehicleType;
	  vehicleDirection = other.vehicleDirection;
	  vehicleTurn = other.vehicleTurn;
	  turning = other.turning;
		len = other.len;

	  return *this;
	}

	//move operator
	VehicleBase& VehicleBase::operator=(VehicleBase&& other) noexcept {
	  if(this == &other){
	    return *this;
	  }
		std::cout << "MOVING " << other.vehicleID << std::endl;
	  vehicleID = other.vehicleID;
	  vehicleType = other.vehicleType;
	  vehicleDirection = other.vehicleDirection;
	  vehicleTurn = other.vehicleTurn;
	  turning = other.turning;
		len = other.len;

	  other.vehicleID = 0;
	  other.vehicleType = static_cast<VehicleType>(999);
	  other.vehicleDirection = static_cast<Direction>(999);
	  other.vehicleTurn = static_cast<Turn>(999);
	  other.turning = false;
		other.len = 0;

	  return *this;
	}

VehicleBase::~VehicleBase() {
	std::cout << "VB Destroyed : " << this << " : " << this->vehicleID << std::endl;
}

#endif
