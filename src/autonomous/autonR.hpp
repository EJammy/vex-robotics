#include "autonSetup.hpp"


void runAutonR()
{
    /* (0,0) is bottom left corner
    * Robot pivot at center
    */
    // start from bottom right.
    setState((matSize-10)*1, 4.5*matSize*1, 180);

    goToGoal(goalR, true);
    backClamp.set(true);
    backLift.set(1);
    mainLift.set(2);
    delay(100);
    moveTo(1.5*matSize, 4.5*matSize);

    moveTo(1.5*matSize, 4*matSize, true);
    lowLift.set(0);
    backClamp.set(false);
    delay(200);
    goToGoal(goalAlliance);
    lowLift.set(1);
    moveTo(2*matSize, 4*matSize, true);
    roller.moveVelocity(rollerVelocity);

    moveTo(2*matSize, 2*matSize, true, 0, 112);
    delay(2000);
}
/*
    // first mobile goal
    // moveTo(2.6*matSize, -1.5*matSize);
    // goToGoal(goalR, true, -2, 20);
    goToGoal(goalR, true);
    clawClampSync();
    lift.moveAbsolute(liftMidPos, liftVelocity);

    moveToRev(3.5*matSize, 3*matSize);
    delay(2000);
    moveTo(1.3*matSize, 5*matSize - rsHalf);
    clawReleaseSync();
    moveToRev(matSize, 5*matSize - rsHalf);


    clearLine();
*/