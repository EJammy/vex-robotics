#include "autonSetup.hpp"

void liftSequence(bool side, bool dir) {
    Lift &lift = (dir? backLift : mainLift);
    if (side) {
        moveTo(4*matSize, 3*matSize, dir);
        moveTo(5*matSize - 6, 3 * matSize, dir);
    }else {
        moveTo(2*matSize, 3*matSize, true);
        moveTo(1*matSize + 6, 3 * matSize, dir);
    }
    lift.move(1, -80);
    delay(1200);
    if (dir)
        backClamp.set(false);
    else
        frontClamp.set(false);
    delay(200);
    lift.set(2);
    delay(200);

    if (side) {
        moveTo(4*matSize, 3*matSize, !dir);
    }else {
        moveTo(2*matSize, 3*matSize, !dir);
    }
}

void runAutonSkill()
{
    // start from bottom right.
    setState(matSize - 8, 4.5*matSize+2, 0);
    // setState(0);

    lowLift.set(0);
    mainLift.set(2);
    delay(800);

    doNxtUpd = false;
    goToGoal(goalAlliance, false, 140, 10);
    lowLift.set(1);
    delay(800);
    roller.moveVelocity(rollerVelocity);

    goToGoal(goalR + Pos{0, -12}, true);
    backClamp.set(true);
    backLift.set(2);

    liftSequence(true);
    backLift.set(0);

    goToGoal(goalM, true);
    backClamp.set(true);
    backLift.set(2);
    liftSequence(false);

}