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

//! Move the character.
static void doMove(std::shared_ptr<Character> c)
{
	ivec2 facing = { 0, 0 };
	switch (randInt(0, 3)) {
	case 0: facing = { -1, 0 }; break;
	case 1: facing = { +1, 0 }; break;
	case 2: facing = { 0, -1 }; break;
	case 3: facing = { 0, +1 }; break;
	}
	c->moveByTile(facing);
}

//! Decide whether or not to move.
static void maybeMove(std::weak_ptr<Character>& c, int chance)
{
	if (randInt(1, chance) == 1)
		doMove(c.lock());
}

std::function<void (time_t)>
AIWanderTile(std::weak_ptr<Character> c, int chance, time_t tryEvery)
{
	assert(conf.moveMode == TILE);

	Cooldown cooldown(tryEvery);
	return [c, chance, cooldown] (time_t dt) mutable {
		if (c.expired()) {
			Log::err("AIWanderTurn", "Character expired");
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
