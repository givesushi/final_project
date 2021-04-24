#ifndef __VEHICLE_BASE_H__
#define __VEHICLE_BASE_H__

// enum: see http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#S-enum
enum class Direction   {north, east, south, west};
enum class VehicleType {car, suv, truck};
enum class LightColor  {green, yellow, red};
enum class Turn 			 {straight, right, left};

#include <iostream>
using namespace std;

class VehicleBase
{
   public:
      static int vehicleCount;

   private:
      int         vehicleID;
      VehicleType vehicleType;
      Direction   vehicleDirection;
			Turn 				vehicleTurn;
			bool 				turning;

   public:
      VehicleBase(VehicleType type, Direction originalDirection, Turn turn);
      VehicleBase(const VehicleBase& other);
      ~VehicleBase();

      inline int getVehicleID() const { return this->vehicleID; }

      inline VehicleType getVehicleType() const { return this->vehicleType; }
      inline Direction   getVehicleOriginalDirection() const { return this->vehicleDirection; }
			inline Turn 			 getVehicleTurn() const { return this->vehicleTurn; }
			inline bool 			 isTurning() { return this->turning; }
			inline void 			 start_turn() { turning = true; }
};

#endif
