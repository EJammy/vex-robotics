#include "autonSetup.hpp"

void autonTest()
{
    chassis->setState({0_in, 0_in, 0_deg});
    // moveTo(matSize, 0);
    moveTo(-matSize, -matSize);
    // moveTo(0, matSize*2);
    // moveTo(0, 0);

    delay(1000);
}