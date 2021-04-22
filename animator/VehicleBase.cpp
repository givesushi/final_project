#ifndef __VEHICLE_BASE_CPP__
#define __VEHICLE_BASE_CPP__

#include "VehicleBase.h"

int VehicleBase::vehicleCount = 0;

VehicleBase::VehicleBase(VehicleType type, Direction originalDirection, Turn t)
    : vehicleID(VehicleBase::vehicleCount++),
      vehicleType(type),
      vehicleDirection(originalDirection),
			turn(t),
			turning(false)
{
	switch (type) {
		case VehicleType::car:
			len = 2;
			break;
		case VehicleType::suv:
			len = 3;
			break;
		case VehicleType::truck:
			len = 4;
			break;
	}
}

VehicleBase::VehicleBase(const VehicleBase& other)
    : vehicleID(other.vehicleID),
      vehicleType(other.vehicleType),
      vehicleDirection(other.vehicleDirection),
			turn(other.turn),
			turning(other.turning),
			len(other.len)
{}

VehicleBase::~VehicleBase() {}

#endif
