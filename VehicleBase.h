#ifndef __VEHICLE_BASE_H__
#define __VEHICLE_BASE_H__

// enum: see http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#S-enum
enum class Direction   {north, south, east, west};
enum class VehicleType {car, suv, truck};
enum class Turn 			 {right, left, straight};
enum class LightColor  {green, yellow, red};

#include <iostream>

class VehicleBase
{
   public:
      static int vehicleCount;

   private:
      int         vehicleID;
      VehicleType vehicleType;
      Direction   vehicleDirection;
			Turn 				turn;
			bool 				turning;
			int 				len;

   public:
      VehicleBase(VehicleType type, Direction originalDirection, Turn t);
      VehicleBase(const VehicleBase& other);
      ~VehicleBase();

      inline int 				 getVehicleID() const { return this->vehicleID; }
      inline VehicleType getVehicleType() const { return this->vehicleType; }
      inline Direction   getVehicleOriginalDirection() const { return this->vehicleDirection; }
			inline Turn 			 getVehicleTurn() const { return this->turn; }
			inline int 				 get_len() const { return this->len; }
			inline bool		 		 isTurning() const { return this->turning; }
			inline void 			 start_turn() { this->turning = true; }

			// VehicleBase& operator=(const VehicleBase&& other);
};

#endif
