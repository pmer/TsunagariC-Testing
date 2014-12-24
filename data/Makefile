DATAFILE := testing.world
CONTENTS := $(shell find . | fgrep -v Makefile | fgrep -v testing.world)

all: $(DATAFILE)

$(DATAFILE): $(CONTENTS)
	zip --symlinks -0 $(DATAFILE) $(CONTENTS)

clean:
	$(RM) $(DATAFILE)

.PHONY: clean
