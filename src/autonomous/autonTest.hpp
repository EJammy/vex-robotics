#include "autonSetup.hpp"

void autonTest()
{
    chassis->setState({0_in, 0_in, 0_deg});
    for (int i = 0; i < 3; i++) {
        moveTo(matSize, 0);
        moveTo(matSize, matSize);
        moveTo(0, matSize);
        moveTo(0, 0);
    }
}