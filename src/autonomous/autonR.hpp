#include "autonSetup.hpp"


void runAutonR()
{

    /* (0,0) is bottom left corner
    * Robot pivot at center
    */
    // start from bottom right.
    chassis->setState({(matSize-rsHalf)*1_in, 4.5*matSize*1_in, 0_deg});
    goToGoalRev(goalR);
    clamp2.set(1);
    moveTo(1.5*matSize, 4.5*matSize);
    lift1.set;
    lift3 = 0;//lift 3 bot
    clamp2.set(0);
    moveTo(1.5 * matSize, 5.5 * matSize);
    lift3 = 1;//lift 3 mid
    roller.moveVelocity(rollerVelocity);
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