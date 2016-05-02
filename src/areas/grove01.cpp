#include <math.h>

#include "../../TsunagariC/src/area.h"
#include "../../TsunagariC/src/log.h"
#include "../../TsunagariC/src/music.h"
#include "../../TsunagariC/src/npc.h"
#include "../../TsunagariC/src/overlay.h"

#include "../../TsunagariC/src/data/data-area.h"

#include "../clouds.h"

#include "../ai/ai-wander.h"

// Circular in-out ease
static double ease(double x)
{
    return 0.5 * sin(M_PI * x - M_PI_2) + 0.5;
}

class grove01 : public DataArea
{
    Clouds clouds;

    bool drinking = false;

    bool openedChest = false;

public:
    grove01() {
        clouds.setZ(10.0);

        scripts["well"] = (TileScript)&grove01::onWell;
        scripts["open_chest"] = (TileScript)&grove01::onOpenChest;
    }

    void onLoad() {
        // Create a wandering wizard NPC.
        auto wizard = area->spawnNPC("entities/wizard/wizard.xml",
            vicoord(16, 22, 0.0), "down");
        wizard->attach(AIWanderTile(wizard, 4, 1000));

        // And a few drifting cloud Overlays.
        for (int i = 0; i < 5; i++)
            clouds.createRandomCloud(*this);

        const int second = 1000;
        clouds.createCloudsRegularly(*this, 10 * second, 20 * second);
    }

    void onWell(Entity&, Tile&) {
        const int maxAlpha = 192;

        if (drinking)
            return;

        drinking = true;

        playSoundEffect("sounds/splash.oga");

        timerProgressAndThen(1000,
            [&] (double percent) {
                uint8_t alpha;
                if (percent < 0.5)
                    alpha = (uint8_t)(maxAlpha * ease(2 * percent));
                else
                    alpha = (uint8_t)(maxAlpha * ease(2 * (1 - percent)));
                area->setColorOverlay(alpha, 255, 255, 255);
            },
            [&] () {
                area->setColorOverlay(0, 0, 0, 0);
                drinking = false;
            }
        );
    }

    void onOpenChest(Entity&, Tile&) {
        /* This function is called when the chest in grove01.tmx is
         * activated by the player. The first time we are run, we open
         * the chest.  Further invocations feature an easter egg where
         * we toggle the game's music. :)
         */

        if (openedChest) {
            toggleMusic();
            return;
        }

        openedChest = true;
        auto tile = area->getTile(5, 21, -0.1); // closed chest
        auto tile2 = tile->offset(0, -1); // above the closed chest
        auto objects = area->getTileSet("areas/tiles/objects.png");

        // Change to open chest, bottom and top halves.
        tile->setType(objects->at(1, 6));
        tile2->setType(objects->at(1, 5));
        area->requestRedraw();

        playSoundEffect("sounds/door.oga");
    }

    void toggleMusic() {
        Music& music = Music::instance();
        if (music.paused()) {
            music.resume();
            Log::info("grove01", "Unpausing music!");
        }
        else {
            music.pause();
            Log::info("grove01", "Pausing music!");
        }
    }
};
