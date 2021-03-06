#include "autonSetup.hpp"

void liftSequence(bool side, bool dir, double diff = 0) {
    double Vel1 = 90;
    double Vel2 = 120;
    Lift &lift = (dir? backLift : mainLift);
    if (side) {
        moveTo(5*matSize - 5, 3 * matSize + diff, dir, 0, Vel1);
    }else {
        moveTo(1*matSize + 5, 3 * matSize + diff, dir, 0, Vel1);
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
        moveTo(4.2*matSize, 3*matSize, !dir, 0, Vel2);
    }else {
        moveTo(1.8*matSize, 3*matSize, !dir, 0, Vel2);
    }updPos();
}

void runAutonSkill()
{
    // start from bottom right.
    // setState(0.5 * matSize, matSize - 8, 90);
    setState(90);
    roller.moveVelocity(rollerVelocity);

    goToGoal(goalAlliance2, false, mxV2, 11.5);
    frontClamp.set(true);
    mainLift.set(2);
    delay(2000);

    moveTo(1.4 * matSize, 1.2 * matSize, true);
    moveTo(1.6 * matSize, 4.4 * matSize, true); updPos();
    goToGoal(goalAlliance, true, 40);
    backClamp.set(true);
    backLift.set(2);
    delay(500);

    moveTo(4 * matSize, 5.5 * matSize, true);
    moveTo(4*matSize, 3*matSize, true); updPos();
    liftSequence(true, true);
    liftSequence(true, false);

    backLift.set(0);
    mainLift.set(0);
    delay(400);

    goToGoal(goalM, true);
    backClamp.set(true);
    liftSequence(true, false);

    goToGoal(goalR);
    frontClamp.set(true);
}