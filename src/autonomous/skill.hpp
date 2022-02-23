#include "autonSetup.hpp"

void runAutonSkill()
{
    // start from bottom left.
    setState(0.5*matSize, matSize, 90);
    goToGoal(goalAlliance2);
    frontClamp.set(true);
    mainLift.set(2);
    moveTo(1.5*matSize, matSize, true);

    goToGoal(goalAlliance, true);
    backClamp.set(true);
    backLift.set(1);

    moveTo(2*matSize, 2*matSize);
    moveTo(4*matSize, 3.2*matSize);
    mainLift.set(2);
    backLift.set(2);
    moveTo(5*matSize, 3.2*matSize, false, 0, 50);
    frontClamp.set(false);
    int x = 0;
    for (int i = 0; i < 10; i++) {
        x += i;
    }
}