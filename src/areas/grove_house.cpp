/********************************
** Tsunagari Tile Engine       **
** grove_house.cpp             **
** Copyright 2016 Paul Merrill **
********************************/

// **********
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// **********

#include "../../TsunagariC/src/data/data-area.h"

#include "../../TsunagariC/src/area.h"
#include "../../TsunagariC/src/tile.h"

class grove_house : public DataArea {
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

        auto tileSet = area->getTileSet("areas/tiles/indoors.png");

        // closed exit on north wall, graphics layer
        auto door_graph = area->getTile(4, 0, -0.2);
        // change to open exit
        door_graph->setType(tileSet->at(2, 9));

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
