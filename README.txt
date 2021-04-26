Jordan Secret
Jacob Pickett
Jake Carlson

README explaining design decisions and how to compile and run the code.

Use makefile to compile the code. To run the code, use command-line arguments following this template:

./simulation [input file] [initial seed]

Where the first argument is the name of the parameter-values input file, and the second argument is the initial seed passed to the random number generator.

Each driver has a double variable for each type of vehicle and direction, which are calculated so that the user only has to generate one random number to
decide which type of vehicle to make in each lane.

The program uses a coordinate system with each lane next to each other so that translations are constant for turns and continuing straight. The sections in the intersection that overlap are similarly checked for. The lanes also correspond with the y-coordinates and order of the enum class and it comes in handy that NB/SB are even and the EB/WB are odd. 

___________________________________________________
NB (0,0)|(1,0)|(2,0)|(3,0)|(4,0)|(5,0)|(6,0)|(7,0)|
___________________________________________________
EB (0,1)|(1,1)|(2,1)|(3,1)|(4,1)|(5,1)|(6,1)|(7,1)|
___________________________________________________
SB (0,2)|(1,2)|(2,2)|(3,2)|(4,2)|(5,2)|(6,2)|(7,2)|
___________________________________________________
WB (0,3)|(1,3)|(2,3)|(3,3)|(4,3)|(5,3)|(6,3)|(7,3)|
____________________^___________^__________________
										INTERSECTION
Conflicting Points (3,0)->(4,1)  Each are a (1,1) vector away
									 (3,1)->(4,2)  from conflict points when you
									 (3,2)->(4,3)  wrap around the y coordinates
									 (3,3)->(4,0)  and at the second point in the
									 intersection it is a (0,-1) translation away
									 both also come in handy for shifting right and
									 left turns.


We used test-driven development (TDD) to create this program...
