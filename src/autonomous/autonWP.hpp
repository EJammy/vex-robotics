#include "autonSetup.hpp"

void runAutonWP()
{

    /* (0,0) is bottom left corner, start from bottom right.
    * Robot pivot at center
    */
    // chassis->setState({(matSize-rsHalf)*1_in, -1.5*matSize*1_in, 0_deg});
    chassis->setState({(matSize-rsHalf)*1_in, 4.5*matSize*1_in, 0_deg});

    // first mobile goal
    // moveTo(2.6*matSize, -1.5*matSize);
    goToGoal(goalR);
    clawClampSync();
    lift.moveAbsolute(60, liftVelocity);

    moveToRev(matSize, 5*matSize - rsHalf);
    clawReleaseSync();
    moveToRev(matSize-rsHalf, 5*matSize - rsHalf);

    goToGoalRev(goalAlliance, false);
}