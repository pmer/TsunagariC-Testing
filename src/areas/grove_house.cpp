#include "../../TsunagariC/src/area.h"
#include "../../TsunagariC/src/tile.h"

#include "../../TsunagariC/src/data/data-area.h"

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
        if (openedDoor) {
            Log::err("grove_house", "onOpenDoor called again");
            return;
        }
        openedDoor = true;

        // torch which activated this trigger should make "ouch" now
        auto torch_prop = area->getTile(6, 0, 0.0);
        torch_prop->useScript = scripts["sound_ouch"];

        // closed exit on north wall, property layer
        auto door_prop = area->getTile(4, 0, 0.0);
        door_prop->setNormalExit(Exit("areas/secret_room.tmx", 4, 5, 0.0));
        door_prop->flagManip().setNowalk(false);

        // closed exit on north wall, graphics layer
        auto door_graph = area->getTile(4, 0, -0.2);
        // change to open exit
        door_graph->setType(area->getTileSet("areas/tiles/indoors.png")->at(2, 9));

        area->requestRedraw();

        playSoundEffect("sounds/door.oga");
    }

    void armorSound() {
        playSoundEffect("sounds/metal_clank.oga");
    }

    void bookSound() {
        playSoundEffect("sounds/book.oga");
    }

    void ouchSound() {
        playSoundEffect("sounds/ouch.oga");
    }
};
