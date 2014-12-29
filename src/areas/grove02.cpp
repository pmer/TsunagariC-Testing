#include "../../TsunagariC/src/area.h"
#include "../../TsunagariC/src/log.h"
#include "../../TsunagariC/src/music.h"
#include "../../TsunagariC/src/random.h"

#include "../../TsunagariC/src/data/area.h"

class grove02 : public DataArea
{
	bool openedChest = false;

public:
	grove02() {
		scripts["open_chest"] = (TileScript)&grove02::onOpenChest;
	}

	void onOpenChest(Entity&, Tile&) {
		/* This function is called when the chest in grove02.tmx is
		 * activated by the player. The first time we are run, we open
		 * the chest.  Further invocations feature an easter egg where
		 * we toggle the game's music. :)
		 */

		if (openedChest) {
			toggleMusic();
			return;
		}

		openedChest = true;
		auto tile = area->getTile(5, 2, -0.05); // closed chest
		auto tile2 = tile->offset(0, -1); // above the closed chest
		auto objects = area->getTileSet("areas/tiles/objects.png");

		// Change to open chest, bottom and top halves.
		tile->setType(objects->at(1, 6));
		tile2->setType(objects->at(1, 5));
		area->requestRedraw();

		Sounds::instance().play("sounds/door.oga")
			->speed(1.0 + randFloat(-0.1, 0.1));
	}

	void toggleMusic() {
		Music& music = Music::instance();
		if (music.isPaused()) {
			music.setPaused(false);
			Log::info("grove02", "Unpausing music!");
		}
		else {
			music.setPaused(true);
			Log::info("grove02", "Pausing music!");
		}
	}
};
