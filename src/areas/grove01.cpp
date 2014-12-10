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

	void onTick() {
		static constexpr double duration = 1.0;
		static constexpr int maxAlpha = 192;

		if (drinking == true) {
			int overlayAlpha;

			double progress = wellTimer.count() / duration;
			if (progress < 0.5)
				overlayAlpha = int(2 * maxAlpha * progress);
			else if (progress < 1.0)
				overlayAlpha = int(2 * maxAlpha * (1 - progress));
			else {
				overlayAlpha = 0;
				drinking = false;
			}

			area->setColorOverlay(255, 255, 255, overlayAlpha); // white overlay
		}
	}

	void onWell(Entity&, Tile&) {
		if (drinking == false) {
			drinking = true;

			wellTimer.reset();
			wellTimer.setRunning(true);

			auto splash = SoundManager::instance().play("sounds/splash.oga");
			splash->setSpeed(1.0 + randFloat(-0.1, 0.1));
		}
	}
};
