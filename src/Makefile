include ../TsunagariC/src/Makefile.common

OBJECTS = clouds.o world.o ai/ai-wander.o
WORLDOBJECTS = ../../src/clouds.o ../../src/world.o ../../src/ai/ai-wander.o

all: tsunagari

tsunagari: $(OBJECTS)
	(cd ../TsunagariC/src; $(MAKE) -f Makefile WORLDOBJECTS="$(WORLDOBJECTS)")

clean:
	$(RM) $(OBJECTS)
	(cd ../TsunagariC/src; $(MAKE) -f Makefile clean)

world.o: world.cpp $(wildcard areas/*.h) $(wildcard areas/*.cpp)
ai/ai-wander.o: ai/ai-wander.cpp ../TsunagariC/src/character.h \
 ../TsunagariC/src/cooldown.h
