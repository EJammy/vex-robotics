#include "autonSetup.hpp"

void autonTest()
{
    setState(0, 0, 0);
    while (1){
        rotateTo(15);
        rotateTo(0);
    }
    moveTo(matSize, 0);
    moveTo(matSize, matSize);
    // moveTo(-matSize, -matSize);
    // moveTo(0, matSize*2);
    // moveTo(0, 0);

    delay(1000);
}