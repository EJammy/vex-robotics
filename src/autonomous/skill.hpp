#include "autonSetup.hpp"

void liftSequence(bool side) {
    if (side) {
        moveTo(4*matSize, 3*matSize, true);
        moveTo(5*matSize - 6, 3 * matSize, true);
    }else {
        moveTo(2*matSize, 3*matSize, true);
        moveTo(1*matSize + 6, 3 * matSize, true);
    }
    backLift.move(1, -80);
    delay(1200);
    backClamp.set(false);
    delay(200);
    backLift.set(2);
    delay(200);
}

void runAutonSkill()
{
    // start from bottom left.
    setState(0.5*matSize, matSize-8, 90);
    lowLift.set(0);
    mainLift.set(2);
    delay(800);
    goToGoalT(goalAlliance2);
    lowLift.set(1);
    delay(800);
    roller.moveVelocity(rollerVelocity);

    moveTo(1.5*matSize, matSize, true);
    goToGoal(goalL, true);
    backClamp.set(true);
    backLift.set(2);

    liftSequence(false);

    goToGoalT(goalM, true);
    backClamp.set(true);
    mainLift.set(2);
    liftSequence(true);

}