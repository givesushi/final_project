taking the following probabilities:
prob_new_vehicle_northbound:               0.25
prob_new_vehicle_southbound:               0.1
prob_new_vehicle_eastbound:                0.15
prob_new_vehicle_westbound:                0.15
proportion_of_cars:                        0.6
proportion_of_SUVs:                        0.3
proportion_right_turn_cars:                0.4
proportion_left_turn_cars:                 0.1
proportion_right_turn_SUVs:                0.3
proportion_left_turn_SUVs:                 0.05
proportion_right_turn_trucks:              0.2
proportion_left_turn_trucks:               0.02

we first calculate each percentage and multiply them together. for example:
proportion_of_cars = proportion_of_cars/(proportion_of_cars + proportion_of_SUVs)

is equivalent to:
proportion_of_cars = 0.6/0.9

we don't do this:
prob_new_vehicle_northbound = 0.25/(0.25+0.1+0.15+0.15) = 0.25/0.65

because that's a probability, not a proportion. so:
vb10 = prob_new_vehicle_northbound * proportion_of_cars = 0.25(0.6/0.9) (this comes out to about 0.167)

then we generate a random number out of 1000 (or 1, it doesn't matter). if the value is between 0 to 167, we generate a northbound car, and so on.

then we end up with something like this:

if (random_number_generator < 168) {
   //northbound car
 } elif (251 > random_number_generator >= 168) {
   //northbound truck
 }
 ...
 } elif (random_number_generator > 650) {
  return;
 }
  
