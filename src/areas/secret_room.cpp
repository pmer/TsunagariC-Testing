#include "../../TsunagariC/src/random.h"
#include "../../TsunagariC/src/sound.h"

#include "../../TsunagariC/src/data/area.h"

class secret_room : public DataArea
{
public:
	secret_room() {
		scripts["sound_book"] = (TileScript)&secret_room::bookSound;
		scripts["sound_ouch"] = (TileScript)&secret_room::ouchSound;
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
