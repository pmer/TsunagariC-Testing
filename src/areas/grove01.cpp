#include "../../TsunagariC/src/area.h"
#include "../../TsunagariC/src/log.h"
#include "../../TsunagariC/src/npc.h"
#include "../../TsunagariC/src/overlay.h"
#include "../../TsunagariC/src/random.h"
#include "../../TsunagariC/src/sounds.h"
#include "../../TsunagariC/src/timer.h"

#include "../../TsunagariC/src/data/area.h"

#include "../ai/ai-wander.h"

class grove01 : public DataArea
{
	bool drinking = false;
	Timer wellTimer;

public:
	grove01() {
		scripts["well"] = (TileScript)&grove01::onWell;
	}

	void onLoad() {
		// Create a wandering wizard NPC.
		auto wizard = area->spawnNPC("entities/wizard/wizard.xml",
			vicoord(6, 3, 0.0), "down");
		wizard->attach(AIWanderTile(wizard, 4, 1000));

		// And a drifting cloud Overlay.
		auto cloud = area->spawnOverlay("entities/cloud/cloud.xml",
			vicoord(11, 2, 10.0), "down");
		cloud->drift(ivec2(-400, 0));
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
};
