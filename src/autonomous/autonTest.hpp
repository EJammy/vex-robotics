#include "autonSetup.hpp"

void autonTest()
{
    setState(0, 0, 0);
    bool doRev = 0;
    for (int i = 0; i < 1; i++) {
        moveTo(matSize, 0, doRev);
        moveTo(matSize, matSize, doRev);
        moveTo(0, 0, doRev);
    }
    // moveTo(-matSize, -matSize);
    // moveTo(0, matSize*2);
    // moveTo(0, 0);

    delay(1000);
}