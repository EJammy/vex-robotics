#include "autonSetup.hpp"


void bhl()
{
    chassis->setState({(matSize-rsHalf)*1_in, (matSize-rsHalf)*1_in, 90_deg});
    lift1.set(2);
    lift3.set(0);
    moveTo(matSize, 2*matSize);//move to left Amogo
    lift3.set(1);
    moveToRev(2.5*matSize, 2*matSize);
    roller.moveVelocity(rollerVelocity);
    moveToRev(2*matSize, 3*matSize);
    moveToRev(3*matSize, 3*matSize);//move to tall mogo
    clamp2.set(1);
    moveTo(matSize, matSize);
    roller.moveVelocity(0);
    return;
}