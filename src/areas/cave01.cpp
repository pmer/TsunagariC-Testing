/*************************************
** Tsunagari Tile Engine            **
** cave01.cpp                       **
** Copyright 2016-2019 Paul Merrill **
*************************************/

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

#include "areas/cave01.h"

#include "core/area.h"
#include "core/player.h"
#include "data/inprogress-sound.h"
#include "data/inprogress-timer.h"

/*
#include <future>

class DataExpr {
 public:
    virtual std::future<void> operator()() = 0;

 protected:
    DataExpr() = default;
    virtual ~DataExpr() = default;

 private:
    DataExpr& operator=(const DataExpr&);
};


struct TimelineItem {
    time_t start;
    Unique<DataExpr> expr;
};

typedef vector<TimelineItem> Timeline;


class SetPlayerFreezeExpr : public DataExpr {};
class SetPlayerPhaseExpr : public DataExpr {};
class FadeOutExpr : public DataExpr {};
class PlaySoundExpr : public DataExpr {};
class FadeInExpr : public DataExpr {};

class TimelineExec {
 public:
    void tick(time_t dt);
    void turn();

 private:
   time_t timeRunSoFar;
};
*/

Cave01::Cave01() noexcept {
    scripts[StringView("sound_ouch")] = (TileScript)&Cave01::ouchSound;
}

void
Cave01::onLoad() noexcept {
    /*
    run(Timeline{
        {    0, new SetPlayerFreeze(true) },
        {    0, new SetPlayerPhase("up") },
        {    0, new FadeOut({0, 0, 0}, 0) },
        {    0, new PlaySound("sounds/rockfall.oga") },
        { 5000, new FadeIn(3000) },
        { 8000, new SetPlayerFreeze(false) }
    });
    */

    Player& player = Player::instance();
    player.setFrozen(true);
    player.setPhase("up");
    area->setColorOverlay(255, 0, 0, 0);

    add(new InProgressSound("sounds/rockfall.oga", [this]() {
        add(new InProgressTimer(
                3000,
                [this](float percent) {
                    uint8_t alpha = static_cast<uint8_t>(255 - percent * 255);
                    area->setColorOverlay(alpha, 0, 0, 0);
                },
                [this]() {
                    area->setColorOverlay(0, 0, 0, 0);
                    Player::instance().setFrozen(false);
                }));
    }));
}

void
Cave01::ouchSound(Entity&) noexcept {
    playSoundEffect("sounds/ouch.oga");
}
