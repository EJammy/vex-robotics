#include "autonSetup.hpp"

void autonPlat()
{
    /* (0,0) is bottom left corner
    * Robot pivot at center
    */
    // start from bottom right.
    setState((matSize-8)*1, 4.5*matSize*1, 0);

    // goToGoal(goalR, true);
    moveTo(4*matSize, 4.5*matSize);
    moveTo(4*matSize, 1.5*matSize);
    moveTo(2*matSize, 1.5*matSize);
    moveTo(2*matSize, 3*matSize);
    goToGoal(goalM);
    delay(200);
    frontClamp.set(true);
    mainLift.set(3);
    moveTo(5 * matSize - 9, 3, false, 0, 100);

}