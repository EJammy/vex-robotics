#include "autonSetup.hpp"

void runAutonWP()
{
    chassis->setState({(matSize-rsHalf)*1_in, 1.5*matSize*1_in, 90_deg});//start at left side facing mogo
    moveTo(matSize, 1.5*matSize);//left blue Amogo
    clamp1.set(1);
    lift1.set(1);
    moveToRev(3*matSize, matSize);//left mogo
    clamp2.set(1);
    lift2.set(1);
    moveToRev(4.7*matSize, 3*matSize);//move to blue plat but leave space for turning
    clamp2.set(0);
    moveTo(4.7*matSize, 3*matSize);//turn 180 degrees
    clamp1.set(0);
    lift2.set(0);
    moveToRev(5*matSize, 0.5*matSize);//move to red left amogo
    clamp2.set(1);
    lift2.set(1);
    moveTo(5*matSize, 5.5*matSize);//process of getting right red amogo
    moveTo(6*matSize, 5.5*matSize);//right red amogo;
    clamp1.set(1);
    lift1.set(1);
    moveToRev(3*matSize, 5*matSize);//move to right mogo
    moveToRev(2*matSize, 5*matSize);//push right mogo to homezone
    moveToRev(1.2*matSize, 3*matSize);//move to red plat
    clamp2.set(0);
    moveTo(1.2*matSize, 3*matSize);//turn 180
    clamp1.set(0);
    lift2.set(0);
    moveToRev(5*matSize, 3*matSize);//push tall mogo to blue homezone
}