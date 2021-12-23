#include "autonSetup.hpp"

void autonTest()
{
    chassis->setState({0_in, 0_in, 0_deg});
    moveTo(matSize*2, 0);
    moveTo(matSize*2, 0);
    moveTo(matSize*2, 0);
    moveTo(matSize*2, 0);

    delay(1000);
}