#include "autonSetup.hpp"

void liftSequence(bool side, bool dir, double diff = 0) {
    double Vel1 = 90;
    double Vel2 = 90;
    Lift &lift = (dir? backLift : mainLift);
    double delta = (dir ? 6: 3);
    if (side) {
        moveTo(5*matSize - delta, 3 * matSize + diff, dir, 0, Vel1);
    }else {
        moveTo(1*matSize + delta, 3 * matSize + diff, dir, 0, Vel1);
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
    }
    lift.set(0);
}

void runAutonSkill()
{
    // start from bottom right.
    // setState(0.5 * matSize, matSize - 8, 90);
    setState(90);
    roller.moveVelocity(rollerVelocity);

    goToGoal(goalAlliance2, false, mxV2, 11);
    frontClamp.set(true);
    mainLift.set(2);
    updPos();
    delay(1200);

    moveTo(1.5 * matSize, 1.4 * matSize, true); updPos();
    goToGoal(goalL + Pos{0, -0.2}, true);
    backClamp.set(true);
    backLift.set(2);
    updPos();

    moveTo(4.2*matSize, 3*matSize, true, 2); updPos();
    liftSequence(true, true, -1);
    updPos();
    liftSequence(true, false);
    updPos();
    backLift.set(0);
    mainLift.set(0);

    //

    moveTo(4.5 * matSize, 1.5 * matSize, true); updPos();
    goToGoal(goalEnemy, true, mxV2, 8);
    backClamp.set(true);
    backLift.set(2);

    moveTo(4 * matSize, 2 * matSize); updPos();
    moveTo(matSize, 5 * matSize);
    updPos();
    moveTo(matSize*2, matSize * 3);
    updPos();

    // liftSequence(false, false);
    // updPos();
    liftSequence(false, true);
    updPos();

    moveTo(1.5 * matSize, 4.5 * matSize); updPos();
    goToGoal(goalAlliance);
    frontClamp.set(true);
    mainLift.set(2);
    moveTo(2 * matSize, 4.5 * matSize, true); updPos();
    goToGoal(goalR, true);
    updPos();
    backClamp.set(true);
    backLift.set(2);
    liftSequence(true, true, -5);
    // liftSequence(true, false, 5);
}