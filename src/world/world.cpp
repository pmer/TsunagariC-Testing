/***************************************
** Tsunagari Tile Engine              **
** world.cpp                          **
** Copyright 2014      Michael Reiley **
** Copyright 2014-2019 Paul Merrill   **
***************************************/

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

#include "world/world.h"

#include "areas/big-tree.h"
#include "areas/cave01.h"
#include "areas/grove-house.h"
#include "areas/grove01.h"
#include "areas/grove04.h"
#include "areas/grove06.h"
#include "areas/secret-room.h"
#include "core/log.h"

DataWorld&
DataWorld::instance() noexcept {
    static auto globalTestingDataWorld = new TestingDataWorld;
    return *globalTestingDataWorld;
}


TestingDataWorld::TestingDataWorld() noexcept {
    Log::info("TestingDataWorld", "Hello!");

    about.name = "Testing World";
    about.author = "Michael Reiley and Paul Merrill";
    about.version = "1";

    parameters.moveMode = TILE;

    parameters.viewportResolution = {240, 160};

    parameters.input.persistDelay.initial = 300;
    parameters.input.persistDelay.consecutive = 100;

    parameters.gameStart.player.file = "entities/player/player.json";
    parameters.gameStart.player.phase = "down";

    parameters.gameStart.area = "areas/grove01.json";
    parameters.gameStart.coords = {15, 22, 0};

    datafile = "./testing.world";

    areas["areas/cave01.json"] = new Cave01;
    areas["areas/bigtree.json"] = new BigTreeArea;
    areas["areas/grove_house.json"] = new GroveHouse;
    areas["areas/grove01.json"] = new Grove01;
    areas["areas/grove04.json"] = new Grove04;
    areas["areas/grove06.json"] = new Grove06;
    areas["areas/secret_room.json"] = new SecretRoom;
}

bool
TestingDataWorld::init() noexcept {
    Log::info("TestingDataWorld", "Ready to go");
    return true;
}
