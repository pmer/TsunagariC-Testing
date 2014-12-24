include ../TsunagariC/src/Makefile.common

OBJECTS = world.o
WORLDOBJECTS = ../../src/world.o

all: tsunagari

world.o: world.cpp $(wildcard areas/*.h) $(wildcard areas/*.cpp)

tsunagari: $(OBJECTS)
	(cd ../TsunagariC/src; $(MAKE) -f Makefile WORLDOBJECTS="$(WORLDOBJECTS)")

clean:
	$(RM) $(OBJECTS)
	(cd ../TsunagariC/src; $(MAKE) -f Makefile clean)
