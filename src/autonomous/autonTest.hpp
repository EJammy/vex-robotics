#include "autonSetup.hpp"


void testRotate() {
    rotateTo(90);
    rotateTo(-90);
    rotateTo(-45);
    rotateTo(-60);
    rotateTo(180);
    delay(100);
}

void autonTest()
{
    setState(matSize - 9, 1.5 *matSize, 0);
    updPos();
    moveTo(3*matSize, 5 * matSize);
    return;
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