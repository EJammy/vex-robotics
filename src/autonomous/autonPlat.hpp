#include "autonSetup.hpp"

void autonPlat()
{
    /* (0,0) is bottom left corner
    * Robot pivot at center
    */
    // start from bottom right.
    const double PDIFF = 6;
    setState((matSize-8)*1, 4.5*matSize*1, 180);
    mainLift.set(1);

    roller.moveVelocity(rollerVelocity);

    goToGoalT(goalR, true);
    backClamp.set(true);
    backLift.set(2);
    delay(200);

auto liftSequence = [&] () {
    moveTo(4*matSize, 3*matSize, true);
    moveTo(5*matSize - PDIFF, 3 * matSize, true);
    backLift.move(1, -80);
    delay(1200);
    backClamp.set(false);
    delay(200);
    backLift.set(2);
    delay(200);
}; liftSequence();

    moveTo(4*matSize, 3*matSize);

    while (!control.A()) { delay(10); }

    backLift.set(0);
    goToGoalT(goalL, true);
    backClamp.set(true);
    backLift.set(2);
    delay(200);

    liftSequence();
    moveTo(2*matSize, 3*matSize);
}