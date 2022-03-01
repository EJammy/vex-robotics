#include "autonSetup.hpp"

void runThree()
{
    /* (0,0) is bottom left corner
    * Robot pivot at center
    */
    // start from bottom right.
    setState((matSize-8)*1, 4.5*matSize*1, 180);

    // goToGoal(goalR, true);
    moveTo(4*matSize, 4.5*matSize, true);
    moveTo(4*matSize, 3*matSize, true);
    moveTo(2*matSize, 3*matSize, true);
    moveTo(2*matSize, 1.5*matSize, true);
    moveTo(4*matSize, 1.5*matSize, true);

}