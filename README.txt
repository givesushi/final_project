Jordan Secret
Jacob Pickett
Jake Carlson

Note:
Im imagining the lanes as next to each for the coordinate pairs and in a specific
order so that the translations are constant for turns and straight. Also the
sections in the intersection that over lap are similarly looked for. The lanes
also correspond the y-coordinate and order of the enum class and it comes in handy
that NB/SB are even and the EB/WB are odd. 

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

So far most of the test cases work fine and I think that the issue is with the
ordering of how the vehicles progress.
