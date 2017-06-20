/*************************************
** Tsunagari Tile Engine            **
** ai-wander.cpp                    **
** Copyright 2014 Michael Riley     **
** Copyright 2014-2017 Paul Merrill **
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

#include "ai/ai-wander.h"

#include <algorithm>

#include "core/character.h"
#include "core/client-conf.h"
#include "core/cooldown.h"
#include "util/assert.h"
#include "util/random.h"

static ivec2 randomFacing() {
    switch (randInt(0, 3)) {
    case 0: return { -1, 0 };
    case 1: return { +1, 0 };
    case 2: return { 0, -1 };
    case 3: return { 0, +1 };
    }
    return { 0, 0 };
}

//! Move the character.
static void doMove(Character* c) {
    c->moveByTile(randomFacing());
}

//! Change direction we are facing.
static void doFace(Character* c) {
    c->setFacing(randomFacing());
    c->setAnimationStanding();
}

//! Decide whether or not to move.
static void maybeMove(Character* c, int chance) {
    if (randInt(1, chance) == 1) {
        //doMove(c.lock());
        doMove(c);
    } else if (randInt(1, chance) == 1) {
        //doFace(c.lock());
        doFace(c);
    }
}

std::function<void(time_t)>
AIWanderTile(Character* c, int chance, time_t tryEvery) {
    assert_(conf.moveMode == TILE);

    Cooldown cooldown(tryEvery);
    return [c, chance, cooldown] (time_t dt) mutable {
        cooldown.advance(dt);
        if (cooldown.hasExpired()) {
            cooldown.wrap();
            maybeMove(c, chance);
        }
    };
}

std::function<void()>
AIWanderTurn(Character* c, int chance) {
    assert_(conf.moveMode == TURN);

    return [c, chance] () mutable {
        maybeMove(c, chance);
    };
}
