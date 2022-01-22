#include "autonSetup.hpp"

void runAutonL()
{
    /* (0,0) is bottom left corner
    * Robot pivot at center
    */
    // start @ left

    setState(matSize - rsHalf, matSize, 0);
    goToGoal(goalL);
    clawClampSync();
    lift.moveAbsolute(50, liftVelocity);

    moveToRev(matSize-rsHalf, matSize-rsHalf);
    goToGoalRev(goalAlliance2);
    roller.moveVelocity(rollerVelocity);
    delay(1000);
    roller.moveVelocity(0);


}