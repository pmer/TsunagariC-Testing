/**********************************
** Tsunagari Tile Engine         **
** ai-wander.h                   **
** Copyright 2014 PariahSoft LLC **
** Copyright 2016 Paul Merrill   **
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

#ifndef SRC_AI_AI_WANDER_H_
#define SRC_AI_AI_WANDER_H_

// The wander AI moves characters around in a Pokemon-style fashion.  Every
// once in a while they will move in a random direction by one tile.

#include <time.h>

#include <functional>

#include "util/memory.h"

class Character;

//! Returns a function that, given `time_t dt`, will try to move the character
//! one tile every `tryEvery` milliseconds.  There is a 1-in-`chance` chance
//! that the character will move during a try.
std::function<void(time_t)>
AIWanderTile(Character* c, int chance, time_t tryEvery);

//! Returns a function that will try to move the character one tile every turn.
//! There is a 1-in-`chance` chance that the character will move during a try.
std::function<void()>
AIWanderTurn(Character* c, int chance);

#endif  // SRC_AI_AI_WANDER_H_
