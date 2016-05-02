/**********************************
** Tsunagari Tile Engine         **
** ai-wander.cpp                 **
** Copyright 2014 PariahSoft LLC **
**********************************/

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

#include <assert.h>

#include "../../TsunagariC/src/character.h"
#include "../../TsunagariC/src/client-conf.h"
#include "../../TsunagariC/src/cooldown.h"
#include "../../TsunagariC/src/random.h"

#include "ai-wander.h"

static ivec2 randomFacing()
{
    switch (randInt(0, 3)) {
    case 0: return { -1, 0 };
    case 1: return { +1, 0 };
    case 2: return { 0, -1 };
    case 3: return { 0, +1 };
    }
    return { 0, 0 };
}

//! Move the character.
static void doMove(std::shared_ptr<Character> c)
{
    c->moveByTile(randomFacing());
}

//! Change direction we are facing.
static void doFace(std::shared_ptr<Character> c)
{
    c->setFacing(randomFacing());
    c->setAnimationStanding();
}

//! Decide whether or not to move.
static void maybeMove(std::weak_ptr<Character>& c, int chance)
{
    if (randInt(1, chance) == 1)
        doMove(c.lock());
    else if (randInt(1, chance) == 1)
        doFace(c.lock());
}

std::function<void (time_t)>
AIWanderTile(std::weak_ptr<Character> c, int chance, time_t tryEvery)
{
    assert(conf.moveMode == TILE);

    Cooldown cooldown(tryEvery);
    return [c, chance, cooldown] (time_t dt) mutable {
        if (c.expired()) {
            Log::err("AIWanderTile", "Character expired");
            return;
        }
        cooldown.advance(dt);
        if (cooldown.hasExpired()) {
            cooldown.wrap();
            maybeMove(c, chance);
        }
    };
}

std::function<void ()>
AIWanderTurn(std::weak_ptr<Character> c, int chance)
{
    assert(conf.moveMode == TURN);

    return [c, chance] () mutable {
        if (c.expired()) {
            Log::err("AIWanderTurn", "Character expired");
            return;
        }
        maybeMove(c, chance);
    };
}
