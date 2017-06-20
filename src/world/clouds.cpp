/**********************************
** Tsunagari Tile Engine         **
** clouds.cpp                    **
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

#include "world/clouds.h"

#include <math.h>

#include <algorithm>
#include <string>

#include "core/area.h"
#include "core/formatter.h"
#include "util/random.h"

Clouds::Clouds()
    : z(0.0) {
}

void Clouds::setZ(double z) {
    this->z = z;
}

void Clouds::createRandomCloud(DataArea& dataArea) {
    ivec3 areaDimensions = dataArea.area->getDimensions();

    // Random location in Area.
    vicoord tilePosition(randInt(0, areaDimensions.x),
                         randInt(0, areaDimensions.y),
                         z);

    createCloudAt(dataArea, tilePosition);
}

void Clouds::createCloudsRegularly(DataArea& dataArea, int minMS, int maxMS) {
    int millis = randInt(minMS, maxMS);
    dataArea.timerThen(millis, [this, &dataArea, minMS, maxMS] () {
        ivec3 areaDimensions = dataArea.area->getDimensions();

        // Right-hand-side of the Area.
        vicoord position(areaDimensions.x + 1,
                         randInt(0, areaDimensions.y),
                         z);

        createCloudAt(dataArea, position);

        // Repeat.
        createCloudsRegularly(dataArea, minMS, maxMS);
    });
}

void Clouds::createCloudAt(DataArea& dataArea, vicoord tilePosition) {
    const double secondsToMilliseconds = 1000.0;
    const int left = -1;
    // const int right = 1;

    ivec2 tileDimensions = dataArea.area->getTileDimensions();

    rcoord pixelPosition(tilePosition.x * tileDimensions.x,
                         tilePosition.y * tileDimensions.y,
                         10.0);

    const double minimumAcceptableDistance = tileDimensions.x * 8;

    for (auto& other : clouds) {
        rcoord otherPosition = other->getPixelCoord();
        double dist = pixelPosition.distanceTo(otherPosition);
        if (dist < minimumAcceptableDistance) {
            return;
        }
    }

    std::string type = Formatter("entities/clouds/cloud%.json") % randInt(1, 4);
    auto cloud = dataArea.area->spawnOverlay(type, tilePosition, "stance");

    clouds.push_back(cloud);

    ivec2 cloudSize = cloud->getImageSize();  // in pixels
    int cloudWidthInTiles = static_cast<int>(
            ceil(static_cast<double>(cloudSize.x) /
                 static_cast<double>(tileDimensions.x)));

    // Drift just enough to get off screen.
    int tilesToDrift = left * (tilePosition.x + cloudWidthInTiles);
    ivec2 drift(tilesToDrift * tileDimensions.x, 0);

    int driftDuration = static_cast<int>(
            abs(drift.x) / cloud->getSpeedInPixels() * secondsToMilliseconds);

    cloud->drift(ivec2(drift.x, 0));
    dataArea.timerThen(driftDuration, [this, cloud] () {
        cloud->destroy();

        auto it = std::find(clouds.begin(), clouds.end(), cloud);
        clouds.erase(it);
    });
}
