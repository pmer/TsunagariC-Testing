include ../TsunagariC/src/Makefile.common

OBJECTS = main.o
WORLDOBJECTS = ../../src/main.o

all: ../TsunagariC/src/tsunagari

../TsunagariC/src/tsunagari: $(OBJECTS) ../TsunagariC/src/*.o
	(cd ../TsunagariC/src; $(MAKE) -f Makefile WORLDOBJECTS="$(WORLDOBJECTS)")

clean:
	$(RM) $(OBJECTS)
	(cd ../TsunagariC/src; $(MAKE) -f Makefile clean)
