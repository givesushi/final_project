EXECS = test driver simulation
OBJS = Driver.o Animator.o VehicleBase.o unitTest.o

#### use next two lines for Mac
CC = clang++
CCFLAGS = -std=gnu++2a -stdlib=libc++

#### use next two lines for mathcs* machines:
#CC = g++
#CCFLAGS = -std=c++11

all: $(EXECS)

simulation: Simulate.o VehicleBase.o Driver.o VBFactory.o Animator.o
	$(CC) $(CCFLAGS) $^ -o $@

test: unitTest.o Driver.o VehicleBase.o animator.o
	$(CC) $(CCFLAGS) $^ -o $@

driver: VehicleBase.o Driver.cpp
	$(CC) $(CCFLAGS) $^ -o $@

testAnimator: $(OBJS)
	$(CC) $(CCFLAGS) $^ -o $@

%.o: %.cpp *.h
	$(CC) $(CCFLAGS) -c $<

%.o: %.cpp
	$(CC) $(CCFLAGS) -c $<

clean:
	/bin/rm -f a.out $(OBJS) $(EXECS) Simulation.o
