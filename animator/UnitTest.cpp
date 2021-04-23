#define CATCH_CONFIG_MAIN
#include "Lanes.h"
#include "Catch.hpp"

TEST_CASE("progress lanes"){
	Lanes lanes{5};
	vector<VehicleBase*> vb = lanes.get_nb_lane();
	REQUIRE(vb.empty());
}
