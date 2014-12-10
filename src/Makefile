include ../TsunagariC/src/Makefile.common

OBJECTS = main.o
WORLDOBJECTS = ../../src/main.o

all: ../TsunagariC/src/tsunagari

tsunagari-mac: $(OBJECTS)
	(cd ../TsunagariC/src; $(MAKE) -f Makefile tsunagari-mac WORLDOBJECTS="$(WORLDOBJECTS)")

../TsunagariC/src/tsunagari: $(OBJECTS)
	(cd ../TsunagariC/src; $(MAKE) -f Makefile WORLDOBJECTS="$(WORLDOBJECTS)")

clean:
	$(RM) $(OBJECTS)
	(cd ../TsunagariC/src; $(MAKE) -f Makefile clean)
