#include "autonSetup.hpp"

void liftSequence(bool side, bool dir, double diff = 0) {
    Lift &lift = (dir? backLift : mainLift);
    if (side) {
        moveTo(4*matSize, 3*matSize, dir);updPos();
        moveTo(5*matSize - 6, 3 * matSize + diff, dir);
    }else {
        moveTo(2*matSize, 3*matSize, true);updPos();
        moveTo(1*matSize + 6, 3 * matSize + diff, dir);
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
    }updPos();
}

void runAutonSkill()
{
    // start from bottom right.
    // setState(0.5 * matSize, matSize - 8, 90);
    setState(90);

    goToGoal(goalAlliance2, false, mxV2, 11.5);
    frontClamp.set(true);
    mainLift.set(2);
    delay(2000);

    moveTo(1.5 * matSize, 1.2 * matSize, true);
    moveTo(1.5 * matSize, 4 * matSize, true); updPos();
    goToGoal(goalAlliance, true);
    backClamp.set(true);
    backLift.set(2);
    delay(500);

    moveTo(3 * matSize, 3.6 * matSize, true);
    liftSequence(true, true);
    liftSequence(true, false);

}