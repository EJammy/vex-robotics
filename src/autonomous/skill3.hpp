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
    lift.set(1);
    delay(1200);
    if (dir)
        backClamp.set(false);
    else
        frontClamp.set(false);
    delay(800);
    lift.set(2);
    delay(200);

    if (side) {
        moveTo(4.2*matSize, 3*matSize, !dir, 0, Vel2);
    }else {
        moveTo(1.8*matSize, 3*matSize, !dir, 0, Vel2);
    }updPos();
    lift.set(0);
}

void runAutonSkill()
{
    // start from bottom right.
    // setState(0.5 * matSize, matSize - 8, 90);
    setState(90);
    roller.moveVelocity(rollerVelocity);

    goToGoal(goalAlliance2, false, mxV2, 11); updPos();
    frontClamp.set(true);
    mainLift.set(2);
    delay(2000);

    moveTo(1.5 * matSize, 1.4 * matSize, true); updPos();
    goToGoal(goalL, true);
    backClamp.set(true);
    backLift.set(2);
    delay(500);

    moveTo(4.4*matSize, 3*matSize, true); updPos();
    liftSequence(true, true);
    liftSequence(true, false);

    delay(800);

    //

    moveTo(4.5 * matSize, 1.5 * matSize, true); updPos();
    goToGoal(goalEnemy, true, mxV2, 8);
    backClamp.set(true);
    backLift.set(2);

    moveTo(4 * matSize, 2 * matSize); updPos();
    goToGoal(goalM); updPos();
    frontClamp.set(true);
    mainLift.set(2);
    delay(200);

    liftSequence(false, false);
    liftSequence(false, true);
    delay(800);

    goToGoal(goalAlliance);
    frontClamp.set(0);
    mainLift.set(2);
    goToGoal(goalR, true);
    backClamp.set(true);
    backLift.set(2);
    liftSequence(true, true, -5);
    liftSequence(true, false, 5);
}