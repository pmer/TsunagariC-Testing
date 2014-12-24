/**********************************
** Tsunagari Tile Engine         **
** world.cpp                     **
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

#include "../TsunagariC/src/log.h"

#include "areas/cave01.cpp"
#include "areas/grove_house.cpp"
#include "areas/grove01.cpp"
#include "areas/grove02.cpp"
#include "areas/secret_room.cpp"
#include "world.h"


static TestingDataWorld globalTestingDataWorld;

DataWorld& DataWorld::instance()
{
	return globalTestingDataWorld;
}


TestingDataWorld::TestingDataWorld()
{
	about.name = "Testing World";
	about.author = "PariahSoft";
	about.version = "1";

	parameters.moveMode = TILE;

	parameters.viewportSize = { 160, 160, 0 };

	parameters.input.persistDelay.initial = 300;
	parameters.input.persistDelay.consecutive = 100;

	parameters.gameStart.player.file = "entities/player/player.xml";
	parameters.gameStart.player.phase = "down";

	parameters.gameStart.area = "areas/grove01.tmx";
	parameters.gameStart.coords = { 5, 3, 0 };

	datafile = "./testing.world";

	areas["areas/cave01.tmx"] = DataAreaRef(new cave01());
	areas["areas/grove_house.tmx"] = DataAreaRef(new grove_house());
	areas["areas/grove01.tmx"] = DataAreaRef(new grove01());
	areas["areas/grove02.tmx"] = DataAreaRef(new grove02());
	areas["areas/secret_room.tmx"] = DataAreaRef(new secret_room());
}

TestingDataWorld::~TestingDataWorld()
{
}

bool TestingDataWorld::init()
{
	Log::info("TestingDataWorld", "Hello!");
	return true;
}
