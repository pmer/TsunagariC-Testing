/********************************
** Tsunagari Tile Engine       **
** grove01.cpp                 **
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

#include <math.h>

#include "core/area.h"
#include "core/log.h"
#include "core/music.h"
#include "core/npc.h"
#include "data/data-area.h"

#include "ai/ai-wander.h"
#include "world/clouds.h"

// Circular in-out ease
static double ease(double x) {
    return 0.5 * sin(M_PI * x - M_PI_2) + 0.5;
}

class grove01 : public DataArea {
    Clouds clouds;

    bool drinking = false;

    bool openedChest = false;
    bool musicPaused = false;

 public:
    grove01() {
        clouds.setZ(10.0);

        scripts["well"] = (TileScript)&grove01::onWell;
        scripts["open_chest"] = (TileScript)&grove01::onOpenChest;
    }

    void onLoad() {
        // Create a wandering wizard NPC.
        auto wizard = area->spawnNPC("entities/wizard/wizard.json",
                                     vicoord(16, 22, 0.0), "down");
        wizard->attach(AIWanderTile(wizard.get(), 4, 1000));

        // And a few drifting cloud Overlays.
        for (int i = 0; i < 5; i++) {
            clouds.createRandomCloud(*this);
        }

        const int second = 1000;
        clouds.createCloudsRegularly(*this, 10 * second, 20 * second);
    }

    void onWell(Entity&, Tile&) {
        const int maxAlpha = 192;

        if (drinking) {
            return;
        }

        drinking = true;

        playSoundEffect("sounds/splash.oga");

        timerProgressAndThen(1000,
            [this] (double percent) {
                uint8_t alpha;
                if (percent < 0.5) {
                    alpha = (uint8_t)(maxAlpha * ease(2 * percent));
                } else {
                    alpha = (uint8_t)(maxAlpha * ease(2 * (1 - percent)));
                }
                area->setColorOverlay(alpha, 255, 255, 255);
            },
            [this] () {
                area->setColorOverlay(0, 0, 0, 0);
                drinking = false;
            });
    }

    void onOpenChest(Entity&, Tile&) {
        /* This function is called when the chest in grove01.json is
         * activated by the player. The first time we are run, we open
         * the chest.  Further invocations feature an easter egg where
         * we toggle the game's music. :)
         */

        if (openedChest) {
            toggleMusic();
            return;
        }

        openedChest = true;
        auto tile = area->getTile(vicoord(5, 21, -0.1));   // closed chest
        auto tile2 = area->getTile(vicoord(5, 20, -0.1));  // above the closed chest
        auto objects = area->getTileSet("areas/tiles/objects.png");

        // Change to open chest, bottom and top halves.
        tile->setType(objects->at(1, 6));
        tile2->setType(objects->at(1, 5));
        area->requestRedraw();

        playSoundEffect("sounds/door.oga");
    }

    void toggleMusic() {
        Music& music = Music::instance();
        if (musicPaused) {
            music.resume();
            Log::info("grove01", "Unpausing music!");
        } else {
            music.pause();
            Log::info("grove01", "Pausing music!");
        }
        musicPaused = !musicPaused;
    }
};
