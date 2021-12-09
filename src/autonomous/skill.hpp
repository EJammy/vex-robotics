#include "autonSetup.hpp"

void runAutonSkill()
{
    /* (0,0) is bottom left corner
    * Robot pivot at center
    */
    // start @ left

    chassis->setState({(matSize / 2)*1_in, (matSize - rsHalf)*1_in, -90_deg});
    goToGoalRev(goalAlliance2, false);
    roller.moveVelocity(rollerVelocity);
    backLift.set_value(true);
    delay(1000);
    roller.moveVelocity(0);

    moveTo(matSize, matSize);
    goToGoal(goalL);
    clawClampSync();
    lift.moveAbsolute(liftMidPos, liftVelocity);

    moveTo(4.8 * matSize, 1.5 * matSize);
    clawReleaseSync();
    moveTo(4.5 * matSize, 1.5 * matSize);
    lift.moveAbsolute(liftLowPos, liftVelocity);
    chassis->turnToAngle(-90_deg);
    backLift.set_value(false);
    goToGoal(goalEnemy, false);
    clawClampSync();
    lift.moveAbsolute(liftMidPos, liftVelocity);

    moveToRev(3*matSize, 1.5*matSize);
    goToGoalRev(goalM);
    backLift.set_value(true);
    delay(200);
    moveTo(2 * matSize, 3 * matSize);
    lift.moveAbsolute(liftHighPos, liftVelocity);
    chassis->setMaxVelocity(mxV2);
    moveTo(matSize + rsHalf, 3 * matSize);
    clawRelease();
    moveTo(1.5*matSize, 3 * matSize);
}