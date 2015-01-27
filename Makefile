BIN_FILES := bin bin/tsunagari bin/client.ini bin/testing.world

all: build

build:
	$(MAKE) -C src
	$(MAKE) -C data
	$(MAKE) $(BIN_FILES)

clean:
	$(MAKE) -C src clean
	$(MAKE) -C data clean
	$(RM) -r bin

bin:
	mkdir bin

bin/tsunagari: TsunagariC/src/tsunagari
	cp $< $@

bin/client.ini: TsunagariC/data/client.ini
	cp $< $@

bin/testing.world: data/testing.world
	cp $< $@

.PHONY: build clean
