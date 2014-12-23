#include "../../TsunagariC/src/area.h"
#include "../../TsunagariC/src/player.h"
#include "../../TsunagariC/src/random.h"
#include "../../TsunagariC/src/sound.h"
#include "../../TsunagariC/src/timer.h"

#include "../../TsunagariC/src/data/area.h"

class cave01 : public DataArea
{
	Timer fallGfxTimer;
	SoundInstanceRef fallSnd;
	int fallStage = 0;

public:
	cave01() {
		scripts["sound_ouch"] = (TileScript)&cave01::ouchSound;
	}

	void onLoad() {
		if (fallStage == 0) {
			Player& player = Player::instance();
			player.setFrozen(true);
			player.setPhase("up");
			area->setColorOverlay(255, 0, 0, 0);
			fallSnd = SoundManager::instance().play("sounds/rockfall.oga");
		}
	}

	void onTick(time_t) {
		switch (fallStage) {
		case 0:
			if (!fallSnd->isPlaying()) {
				fallStage++;
				fallGfxTimer.setRunning(true);
			}
			break;
		case 1:
			if (fallGfxTimer.count() < 3.0) {
				double percent = fallGfxTimer.count() / 3.0;
				unsigned char alpha = (unsigned char)(255 - percent * 255);
				area->setColorOverlay(alpha, 0, 0, 0);
			}
			else {
				fallStage++;
				area->setColorOverlay(0, 0, 0, 0);
				Player::instance().setFrozen(false);
			}
			break;
		default:
			break;
		}
	}

	void ouchSound(Entity&, Tile&) {
		auto snd = SoundManager::instance().play("sounds/ouch.oga");
		snd->setSpeed(1.0 + randFloat(-0.1, 0.1));
	}
};
