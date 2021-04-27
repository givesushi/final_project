Jordan Secret
Jacob Pickett
Jake Carlson

README explaining design decisions and how to compile and run the code.

Use makefile to compile the code. To run the code, use command-line arguments following this template:

./simulation [input file] [initial seed]

Where the first argument is the name of the parameter-values input file, and the second argument is the initial seed passed to the random number generator.

Each driver has a double variable for each type of vehicle and direction, which are calculated so that the user only has to generate one random number to
decide which type of vehicle to make in each lane.

We used test-driven development (TDD) to create this program...
