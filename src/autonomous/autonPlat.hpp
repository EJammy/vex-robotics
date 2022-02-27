#include "autonSetup.hpp"

void autonPlat()
{
    /* (0,0) is bottom left corner
    * Robot pivot at center
    */
    // start from bottom right.
    const double PDIFF = 6;
    setState((matSize-8)*1, 4.5*matSize*1, 180);

    roller.moveVelocity(rollerVelocity);

    goToGoal(goalR, true);
    backClamp.set(true);
    backLift.set(2);
    delay(200);

    moveTo(4*matSize, 3*matSize, true);
    moveTo(5*matSize - PDIFF, 3 * matSize, true);
    backLift.move(1, -80);
    delay(1000);
    backClamp.set(false);
    delay(200);
    backLift.set(2);
    delay(200);

    moveTo(4*matSize, 3*matSize, false, 0, 70);
    backLift.set(0);
    goToGoal(goalL);
    backClamp.set(true);
    backLift.set(2);
    delay(200);
    return;

    moveTo(2*matSize, 3*matSize, true);
    moveTo(1*matSize + PDIFF, 3*matSize, true);
    backClamp.set(false);
}