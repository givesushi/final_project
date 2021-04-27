Jordan Secret
Jacob Pickett
Jake Carlson

README explaining design decisions and how to compile and run the code.

To use makefile to compile the code, simply type "make" in the command line from inside the project directory. To run the code,
use command-line arguments following this template:

./simulate [input file] [initial seed]

Where the first argument is the name of the parameter-values input file, and the second argument is the initial seed passed to the random number generator.

To compile the unit testing, do "make test" and run the unit tests with ./test

Design Decisions: 
  
  This project is split up into multiple classes: Lanes.cpp, Driver.cpp, VehicleBase.cpp, Simulate.cpp, and Animator.cpp
  
  Lanes.cpp: 
  A lane object has 4 vectors which represent the lanes going in each direction, and 4 queues used for holding cars that are waiting to enter the simulation. There
  are functions in Lanes.cpp which add a vehicle from each queue to the appropriate lane when a spot opens. There are functions in Lanes.cpp which update the
  position of cars in the lanes vectors on each clock tick. 
  
  Driver.cpp: 
  This class reads the input file and stores all the data. Each driver has a double variable for each type of vehicle, direction and turn, which are calculated so
  that the program only has to generate one random number to decide which type of vehicle to make in each lane. There is a function called generateVehciles which is
  called in the simulation loop for each clock tick.
  
  VehicleBase.cpp: 
  We added to this class so that each vehicle in the simulation could be an VehicleBase instance. This class also has our move and copy constructors and operators.
  
  Simulate.cpp: 
  This class simply has a main method which runs the simulation using a while loop.
  
  Animator.cpp: 
  We altered this class slightly so that it would be compatible with the shared pointers we used in Driver.cpp


We used test-driven development (TDD) to create this program... See UnitTesting.cpp for our tests: 
  
  Driver Tests: 
    We test generateVehicles by creating a double rand, and calling generateVehicles with it. We check that the correct type of vehicles are made. Note that these
    tests are dependent on the sample input file and may not pass if the sample proportions change. We also test that when rand is very high, .99, no vehicles will
    generate.
    
  Lanes Tests: 
    We test adding the the queues by creating VehicleBase objects, passing them to the new_vehicle function in Lanes, and checking the queues. 
    
    We test advancing the lanes vectors by adding VehicleBase objects to the lanes, calling the functions which advance the lanes, and checking that the correct
    positions in each vector are occupied by the correct vehicle. These tests also make sure that the logic for the intersection is working by checking right turns,
    stopping at the light, etc.
    
