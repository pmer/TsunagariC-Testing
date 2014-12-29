#include "../../TsunagariC/src/area.h"
#include "../../TsunagariC/src/random.h"
#include "../../TsunagariC/src/sound.h"
#include "../../TsunagariC/src/tile.h"

#include "../../TsunagariC/src/data/area.h"

class grove_house : public DataArea
{
	bool openedDoor = false;

public:
	grove_house() {
		scripts["open_door"] = (TileScript)&grove_house::onOpenDoor;
		scripts["sound_armor"] = (TileScript)&grove_house::armorSound;
		scripts["sound_book"] = (TileScript)&grove_house::bookSound;
		scripts["sound_ouch"] = (TileScript)&grove_house::ouchSound;
	}

	void onOpenDoor(Entity&, Tile&) {
		if (openedDoor)
			return;
		openedDoor = true;

		// closed exit on north wall, property layer
		auto door_prop = area->getTile(4, 0, 0.0);
		door_prop->setNormalExit(Exit("areas/secret_room.tmx", 4, 5, 0.0));
		door_prop->flagManip().setNowalk(false);

		// closed exit on north wall, graphics layer
		auto door_graph = area->getTile(4, 0, -0.2);
		// change to open exit
		door_graph->setType(area->getTileSet("areas/tiles/indoors.png")->at(2, 9));

		area->requestRedraw();

		Sounds::instance().play("sounds/door.oga")
			->speed(1.0 + randFloat(-0.1, 0.1));
	}

	void armorSound() {
		Sounds::instance().play("sounds/metal_clank.oga")
			->speed(1.0 + randFloat(-0.1, 0.1));
	}

	void bookSound() {
		Sounds::instance().play("sounds/book.oga")
			->speed(1.0 + randFloat(-0.1, 0.1));
	}

	void ouchSound() {
		Sounds::instance().play("sounds/ouch.oga")
			->speed(1.0 + randFloat(-0.1, 0.1));
	}
};
