#include "autonR.hpp"


void runAutonPush()
{
    /* (0,0) is bottom left corner
    * Robot pivot at center
    */
    // start from bottom right.

    chassis->setState({(matSize-rsHalf)*1_in, 4.5*matSize*1_in, 0_deg});

    // first mobile goal
    // moveTo(2.6*matSize, -1.5*matSize);
    moveTo(4*matSize - rsHalf - 5, 4.5*matSize);
    clawClampSync();
    lift.moveAbsolute(liftMidPos, liftVelocity);

    clearLine();
}