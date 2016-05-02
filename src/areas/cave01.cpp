/********************************
** Tsunagari Tile Engine       **
** cave01.cpp                  **
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
#include "../../TsunagariC/src/player.h"

class cave01 : public DataArea {
 public:
    cave01() {
        scripts["sound_ouch"] = (TileScript)&cave01::ouchSound;
    }

    void onLoad() {
        Player& player = Player::instance();
        player.setFrozen(true);
        player.setPhase("up");
        area->setColorOverlay(255, 0, 0, 0);

        playSoundAndThen("sounds/rockfall.oga", [this] () {
            timerProgressAndThen(3000,
                [this] (double percent) {
                    uint8_t alpha = static_cast<uint8_t>(255 - percent * 255);
                    area->setColorOverlay(alpha, 0, 0, 0);
                },
                [this] () {
                    area->setColorOverlay(0, 0, 0, 0);
                    Player::instance().setFrozen(false);
                });
        });
    }

    void ouchSound(Entity&, Tile&) {
        playSoundEffect("sounds/ouch.oga");
    }
};
