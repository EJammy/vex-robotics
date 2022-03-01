#include "autonSetup.hpp"

void autonTest()
{
    // setState((matSize-10)*1, 4.5*matSize*1, 180);
    // moveTo(1.5 * matSize, 4.5*matSize, true);
    // rotateTo(90);
    // return;
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