#ifndef __VEHICLE_BASE_CPP__
#define __VEHICLE_BASE_CPP__

#include "VehicleBase.h"

int VehicleBase::vehicleCount = 0;

VehicleBase::VehicleBase(VehicleType type, Direction direction, Turn turn)
    : vehicleID(VehicleBase::vehicleCount++),
      vehicleType(type),
      vehicleDirection(direction),
			vehicleTurn(turn),
			turning(false)
{}

VehicleBase::VehicleBase(const VehicleBase& other)
    : vehicleID(other.vehicleID),
      vehicleType(other.vehicleType),
      vehicleDirection(other.vehicleDirection),
			vehicleTurn(other.vehicleTurn),
			turning(other.turning)
{}

VehicleBase::~VehicleBase() {
	cout << "VB Destroyed : " << this << " : " << this->vehicleID << endl;
}

#endif
