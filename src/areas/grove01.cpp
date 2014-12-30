#include "../../TsunagariC/src/area.h"
#include "../../TsunagariC/src/log.h"
#include "../../TsunagariC/src/music.h"
#include "../../TsunagariC/src/npc.h"
#include "../../TsunagariC/src/overlay.h"
#include "../../TsunagariC/src/random.h"
#include "../../TsunagariC/src/sounds.h"
#include "../../TsunagariC/src/timer.h"

#include "../../TsunagariC/src/data/data-area.h"

#include "../ai/ai-wander.h"

class grove01 : public DataArea
{
	bool drinking = false;
	Timer wellTimer;

	bool openedChest = false;

public:
	grove01() {
		scripts["well"] = (TileScript)&grove01::onWell;
		scripts["open_chest"] = (TileScript)&grove01::onOpenChest;
	}

	void onLoad() {
		// Create a wandering wizard NPC.
		auto wizard = area->spawnNPC("entities/wizard/wizard.xml",
			vicoord(16, 13, 0.0), "down");
		wizard->attach(AIWanderTile(wizard, 4, 1000));

		// And a drifting cloud Overlay.
		auto cloud = area->spawnOverlay("entities/cloud/cloud.xml",
			vicoord(21, 12, 10.0), "down");
		cloud->drift(ivec2(-1200, 0));
	}

	void onWell(Entity&, Tile&) {
		static constexpr int maxAlpha = 192;

		if (drinking)
			return;

		drinking = true;

		Sounds::instance().play("sounds/splash.oga")
			->speed(1.0 + randFloat(-0.1, 0.1));

		timerProgressAndThen(1000,
			[&] (double percent) {
				uint8_t alpha;
				if (percent < 0.5)
					alpha = (uint8_t)(2 * maxAlpha * percent);
				else
					alpha = (uint8_t)(2 * maxAlpha * (1 - percent));
				area->setColorOverlay(alpha, 255, 255, 255);
			},
			[&] () {
				area->setColorOverlay(0, 0, 0, 0);
				drinking = false;
			}
		);
	}

	void onOpenChest(Entity&, Tile&) {
		/* This function is called when the chest in grove01.tmx is
		 * activated by the player. The first time we are run, we open
		 * the chest.  Further invocations feature an easter egg where
		 * we toggle the game's music. :)
		 */

		if (openedChest) {
			toggleMusic();
			return;
		}

		openedChest = true;
		auto tile = area->getTile(5, 12, -0.05); // closed chest
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
		if (music.paused()) {
			music.resume();
			Log::info("grove01", "Unpausing music!");
		}
		else {
			music.pause();
			Log::info("grove01", "Pausing music!");
		}
	}
};
