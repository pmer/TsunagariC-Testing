#include "../../TsunagariC/src/area.h"
#include "../../TsunagariC/src/random.h"
#include "../../TsunagariC/src/timer.h"

#include "../../TsunagariC/src/data/area.h"

class grove01 : public DataArea
{
	bool drinking = false;
	Timer wellTimer;

public:
	grove01() {
		scripts["well"] = (TileScript)&grove01::onWell;
	}

	void onLoad() {
		auto cloud = area->spawnOverlay("entities/cloud/cloud.xml", 11, 2, 10.0, "down");
		cloud->move(-400, 0);
	}

	void onWell(Entity&, Tile&) {
		static constexpr int maxAlpha = 192;

		if (drinking == false) {
			drinking = true;

			wellTimer.reset();
			wellTimer.setRunning(true);

			auto& sound = SoundManager::instance();
			auto splash = sound.play("sounds/splash.oga");
			splash->setSpeed(1.0 + randFloat(-0.1, 0.1));

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
	}
};
