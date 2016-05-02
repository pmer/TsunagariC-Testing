/**********************************
** Tsunagari Tile Engine         **
** clouds.h                      **
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

#ifndef SRC_CLOUDS_H_
#define SRC_CLOUDS_H_

#include <memory>
#include <vector>

#include "../TsunagariC/src/overlay.h"
#include "../TsunagariC/src/vec.h"

#include "../TsunagariC/src/data/data-area.h"

//! Create clouds that drift left across an Area.
class Clouds
{
public:
    Clouds();

    //! Set spawning z-height layer that clouds will appear on.
    void setZ(double z);

    //! Create a cloud at a random position.  May do nothing if the cloud
    //! would have appeared to close to another cloud (which would be ugly).
    void createRandomCloud(DataArea& dataArea);
    //! Create a sequence of clouds over time that drift in from the
    //! right-hand-side.  One will attempt to appear every [minMS, maxMS]
    //! milliseconds.  May do nothing if the cloud would have appeared to
    //! close to another cloud (which would be ugly).
    void createCloudsRegularly(DataArea& dataArea, int minMS, int maxMS);

private:
    //! Create a cloud, move it left until out of area, then destroy it.
    //! If the cloud would be created next to another, already existing
    //! cloud, do nothing.
    void createCloudAt(DataArea& dataArea, vicoord tilePosition);

    double z;

    std::vector<std::shared_ptr<Overlay>> clouds;
};

#endif  // SRC_CLOUDS_H_
