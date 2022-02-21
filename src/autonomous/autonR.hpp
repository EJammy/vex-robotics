#include "autonSetup.hpp"


void runAutonR()
{
    /* (0,0) is bottom left corner
    * Robot pivot at center
    */
    // start from bottom right.
    setState((matSize-12)*1, 4.5*matSize*1, 180);

    goToGoalRev(goalR);
    clamp2.set(1);
    backLift.set(1);
    mainLift.set(2);
    delay(100);
    moveTo(1.5*matSize, 4.5*matSize);

    moveTo(1.5*matSize, 4*matSize, true);
    lowLift.set(0);
    clamp2.set(0);
    goToGoal(goalAlliance);
    lowLift.set(1);
    delay(500);
    roller.moveVelocity(rollerVelocity);
    // moveToRev(1.5*matSize, 4.8*matSize);
    delay(1000);

    // moveToRev(3*matSize, 5*matSize, 0, 70);
    // moveToRev(3*matSize, 5*matSize, 0, 70);
    moveTo(1.5*matSize, 4.5*matSize);
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