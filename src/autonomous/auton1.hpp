#include "autonSetup.hpp"

void runAuton()
{

     /* (0,0) is bottom right corner, start from bottom right.
      * Robot pivot at center
      */
    chassis->setState({rsHalf*1_in, -(rsHalf + matSize)*1_in, 0_deg});

    // first mobile goal
    // moveTo(2.6*matSize, -1.5*matSize);
    goToGoal(goalR);
    clawClamp();
    delay(500);
    moveToRev(1.5*matSize, -1.5*matSize);
    clawRelease();

    // clear the line (alliance goal)
    moveTo(matSize-rsHalf, -(rsHalf + matSize));
    // moveTo(matSize, -matSize);
    goToGoal(goalAlliance);
    clawClamp();
    moveToRev(matSize/2, -matSize*1.5);
    clawRelease();

    // second mobile goal
    // moveTo(2.7*matSize, -2.7*matSize);
    goToGoal(goalM);
    clawClamp();
    moveToRev(1.5*matSize, -4.5*matSize);
    clawRelease();

    // third mobile goal
    moveTo(2.8*matSize, -4.5*matSize);
    goToGoal(goalL);
    clawClamp();
    moveToRev(1.5*matSize, -4.5*matSize);
    clawRelease();

    delay(5000);
    moveTo(-matSize, 0);
}