#ifndef autonSetup
#define autonSetup

#include "../setup.hpp"
using namespace okapi::literals;
using pros::delay;
const double matSize = 23.42; // distance of a mat on field

// 16.8/2 = 8.4
const double robotSize = 16.8;
const double rsHalf = robotSize/2;

using Pos = std::pair<double, double>;
const Pos goalL = {3*matSize, 1.5*matSize};
const Pos goalM = {3*matSize, 3*matSize};
const Pos goalR = {3*matSize, 4.5*matSize};
const Pos goalAlliance = {1.5*matSize, 5.5*matSize}; // the goal on awp
const Pos goalAlliance2 = { matSize / 2, matSize * 1.75}; // the goal near platform

const Pos goalEnemy = {4.5*matSize, 0.5*matSize};
const Pos goalEnemy2 = {5.5*matSize, 4.25 * matSize };

const double mxV1 = 150;
const double mxV2 = 50;

void clawClampSync()
{
    clawClamp();
    delay(200);
}

void clawReleaseSync()
{
    clawRelease();
    delay(200);
}

const double circumfrence = 4*PI;
void moveFwd(double dist, double velocity = 100) {
    double vInches = velocity/60.0*circumfrence; // velocity in inches
    int t = dist/vInches*1000;
    left.moveVelocity(velocity);
    right.moveVelocity(velocity);
    delay(t*chassisGearRatio);
    left.moveVelocity(0);
    right.moveVelocity(0);
}

void rotateTo(double d) {
    chassis->turnToAngle(d*1_deg);
}

void moveTo(double x, double y, double delta = 0.0, bool wait = true, double velocity = 100)
{
    dist_t xdist = x*1_in;
    dist_t ydist = y*1_in;
    xdist = chassis->getOdometry()->getState().x - xdist;
    ydist = chassis->getOdometry()->getState().y - ydist;

    if (ydist != 0_m)
    {
        auto theta = okapi::atan((xdist / ydist));
        if (ydist > 0_in) theta += 180_deg;
        if (abs(theta) > 2_deg)
            rotateTo(90 - theta.convert(1_deg)); // math checks out
    }
    moveFwd((okapi::sqrt(xdist*xdist + ydist*ydist) - delta*1_in).convert(1_in), velocity);
}


// void moveToRev(double x, double y, double delta = 0.0, bool wait = true, double velocity = -1) // x-axis is vertical axis
// {
//     dist_t xdist = x*1_in;
//     dist_t ydist = y*1_in;
//     xdist = chassis->getOdometry()->getState().x - xdist;
//     ydist = chassis->getOdometry()->getState().y - ydist;

//     if (ydist != 0_m)
//     {
//         auto theta = okapi::atan((xdist / ydist));
//         if (ydist < 0_in) theta += 180_deg;
//         rotateTo(90 - theta.convert(1_deg)); // math checks out
//     }
//     if (velocity != -1) chassis->setMaxVelocity(velocity);
//     chassis->moveDistanceAsync(-okapi::sqrt(xdist*xdist + ydist*ydist) + delta*1_in);
//     if (wait) {
//         wait1();
//     }
// }

void goToGoal(Pos p, double goalDelta = 8)
{
    double x = p.first;
    double y = p.second;
    moveTo(x, y, goalDelta, false);
}

// void goToGoalRev(Pos p, bool twoStep = true, double goalDelta2 = 5, double goalDelta1 = 18)
// {
//     double x = p.first;
//     double y = p.second;
//     if (twoStep) {
//         moveToRev(x, y, goalDelta1, false);
//         wait2();
//     }
//     moveToRev(x, y, goalDelta2, false, mxV2);
//     wait1();

//     chassis->setMaxVelocity(mxV1);
// }

// void turn(double angle, double diff = 0.22) {
//     double targetAngle = 0;
//     PID tpid = PID(0.016, 0.00045, 0.1, 9, 0.15);
//     int t = 0;
//     targetAngle += angle;
//     tpid.setTarget(targetAngle);
//     while (t < 8) {
//         tpid.update(imu.get_rotation());
//         double force = clamp(tpid.getOutput(), 0.7);

//         force *= 12000;
//         left.moveVoltage(force);
//         right.moveVoltage(-force);

//         // if (imu.get_rotation() > targetAngle)
//         // 	chassis->getModel()->rotate(-20);
//         // else
//         // 	chassis->getModel()->rotate(20);
//         if (abs(imu.get_rotation() - targetAngle) < diff) t++;
//         else t = 0;
//         pros::delay(4);
//     }
//     pros::delay(20);
// }

// void clearLine()
// {
//     moveToRev(1.5*matSize, 5*matSize - rsHalf);
//     clawReleaseSync();
//     moveToRev(matSize, 5*matSize - rsHalf);

//     goToGoalRev(goalAlliance, false, 5, 20);
//     roller.moveRelative(1000, rollerVelocity);
//     delay(2000);
// }
#endif

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
