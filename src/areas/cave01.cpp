#include "../../TsunagariC/src/area.h"
#include "../../TsunagariC/src/player.h"
#include "../../TsunagariC/src/random.h"
#include "../../TsunagariC/src/sounds.h"

#include "../../TsunagariC/src/data/data-area.h"

class cave01 : public DataArea
{
public:
	cave01() {
		scripts["sound_ouch"] = (TileScript)&cave01::ouchSound;
	}

	void onLoad() {
		Player& player = Player::instance();
		player.setFrozen(true);
		player.setPhase("up");
		area->setColorOverlay(255, 0, 0, 0);

		playSoundAndThen("sounds/rockfall.oga", [&] () {
			timerProgressAndThen(3000,
				[&] (double percent) {
					uint8_t alpha = (uint8_t)(255 - percent * 255);
					area->setColorOverlay(alpha, 0, 0, 0);
				},
				[&] () {
					area->setColorOverlay(0, 0, 0, 0);
					Player::instance().setFrozen(false);
				}
			);
		});

	}

	void ouchSound(Entity&, Tile&) {
		Sounds::instance().play("sounds/ouch.oga")
			->speed(1.0 + randFloat(-0.1, 0.1));
	}
};
