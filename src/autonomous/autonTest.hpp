#include "autonSetup.hpp"

void autonTest()
{
    setState(0, 0, 0);
    moveFwd(-20);
    return;
    bool doRev = 1;
    for (int i = 0; i < 3; i++) {
        moveTo(matSize, 0, doRev);
    delay(1000);
        moveTo(matSize, matSize, doRev);
    delay(1000);
        moveTo(0, 0, doRev);
    delay(1000);
    }
    // moveTo(-matSize, -matSize);
    // moveTo(0, matSize*2);
    // moveTo(0, 0);

    delay(1000);
}