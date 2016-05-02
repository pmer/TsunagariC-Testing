#include "../../TsunagariC/src/data/data-area.h"

#include "../clouds.h"

class bigtree : public DataArea
{
    Clouds clouds;

public:
    bigtree() {
        clouds.setZ(10.0);
    }

    void onLoad() {
        clouds.createRandomCloud(*this);

        const int second = 1000;
        clouds.createCloudsRegularly(*this, 30 * second, 60 * second);
    }
};
