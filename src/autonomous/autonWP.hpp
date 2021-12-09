#include "autonSetup.hpp"

void runAutonWP()
{
    /* (0,0) is bottom left corner
    * Robot pivot at center
    */
    // start @ left

    chassis->setState({(matSize / 2)*1_in, (matSize - rsHalf)*1_in, -90_deg});
    goToGoalRev(goalAlliance2);
    roller.moveVelocity(170);
    delay(1000);
    roller.moveVelocity(0);

    lift.moveAbsolute(50, liftVelocity);
    moveTo(1.5 * matSize, 1.5 * matSize);
    moveTo(1.5 * matSize, 5.5 * matSize);
    clawClampSync();


}