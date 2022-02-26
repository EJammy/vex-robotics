#include "autonSetup.hpp"

void runAutonL()
{
    /* (0,0) is bottom left corner
    * Robot pivot at center
    */
    // start @ left

    setState(matSize - 9, 1*matSize, 180);
    goToGoal(goalL, true);
    backClamp.set(true);
    delay(200);
    backLift.set(1);

    mainLift.set(2);
    moveTo(1 * matSize - 8, 1*matSize - 5);
    backClamp.set(0);
    backLift.set(0);
    delay(500);

    rotateToPt(goalAlliance2.first, goalAlliance2.second);
    lowLift.set(0);
    delay(1000);
    goToGoal(goalAlliance2);
    lowLift.set(1);
    delay(1000);
    roller.moveVelocity(rollerVelocity);
    delay(5000);
    roller.moveVelocity(0);


}