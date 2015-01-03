#include "../../TsunagariC/src/data/data-area.h"

class secret_room : public DataArea
{
public:
	secret_room() {
		scripts["sound_book"] = (TileScript)&secret_room::bookSound;
		scripts["sound_ouch"] = (TileScript)&secret_room::ouchSound;
	}

	void bookSound() {
		playSoundEffect("sounds/book.oga");
	}

	void ouchSound() {
		playSoundEffect("sounds/ouch.oga");
	}
};
