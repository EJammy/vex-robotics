#include "autonSetup.hpp"

void autonTest()
{
    chassis->setState({0_in, 0_in, 0_deg});
    moveFwd(2*matSize, 200);
}