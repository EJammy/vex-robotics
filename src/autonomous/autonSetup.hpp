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
const double mxV2 = 100;
const double circumfrence = 4*PI;
const int move_t_extra = 80;
const int autonVelocity = 10;

void moveFwd(double dist, double velocity = mxV1, bool stop = true) {
    double vInches = velocity/60.0*circumfrence; // velocity in inches
    int t = dist/vInches*1000;
    left.moveVelocity(velocity);
    right.moveVelocity(velocity);
    delay(t*chassisGearRatio + move_t_extra);
    if (stop) {
        left.moveVelocity(0);
        right.moveVelocity(0);
        delay(300);
    }
}
    // dist = dist/circumfrence*360;
    // left.moveRelative(dist, velocity);
    // right.moveRelative(dist, velocity);
    // delay(5000);
    // while (!left.isStopped() || !right.isStopped()) delay(100);

void moveRev(double dist, double velocity = mxV1, bool stop = true) {
    moveFwd(dist, -velocity, stop);
}

void rotateTo(double d) {
    chassis->turnToAngle(d*1_deg);
}
void rotateToR(double d) {
    double deg = chassis->getOdometry()->getState().theta.convert(1_deg);
    while (d - deg < 0) d += 360;
    rotateTo(d);
}

void rotateToL(double d) {
    double deg = chassis->getOdometry()->getState().theta.convert(1_deg);
    while (d - deg > 0) d -= 360;
    rotateTo(d);
}

const double minDistEpsilon = 2;
void moveTo(double x, double y, double delta = 0.0, double velocity = mxV1, bool stop = true)
{
    dist_t xdist = x*1_in - chassis->getOdometry()->getState().x;
    dist_t ydist = y*1_in - chassis->getOdometry()->getState().y;
    if ((xdist * xdist + ydist * ydist).convert(1_in*1_in) < minDistEpsilon * minDistEpsilon)
        return;

    double deg = chassis->getOdometry()->getState().theta.convert(1_deg);
    if (ydist != 0_m)
    {
        auto theta = okapi::atan((xdist / ydist)).convert(1_deg);
        if (ydist < 0_in) theta += 180;
        theta = 90 - theta;
        while (theta - deg < -180) theta += 360;
        while (theta - deg > 180) theta -= 360;
        if (abs(theta) > 2)
            rotateTo(theta); // math checks out
    }
    int t = 4;
    // while ((xdist * xdist + ydist * ydist).convert(1_in*1_in) > minDistEpsilon * minDistEpsilon && t--) {
    //     dist_t xdist = x*1_in - chassis->getOdometry()->getState().x;
    //     dist_t ydist = y*1_in - chassis->getOdometry()->getState().y;
        moveFwd((okapi::sqrt(xdist*xdist + ydist*ydist) - delta*1_in).convert(1_in), velocity, stop);
    // }
}

void moveToRev(double x, double y, double delta = 0.0, double velocity = mxV1, bool stop = true)
{
    dist_t xdist = x*1_in - chassis->getOdometry()->getState().x;
    dist_t ydist = y*1_in - chassis->getOdometry()->getState().y;
    if ((xdist * xdist + ydist * ydist).convert(1_in*1_in) < minDistEpsilon * minDistEpsilon)
        return;

    double deg = chassis->getOdometry()->getState().theta.convert(1_deg);
    if (ydist != 0_m)
    {
        auto theta = okapi::atan((xdist / ydist)).convert(1_deg);
        if (ydist > 0_in) theta += 180;
        theta = 90 - theta;
        while (theta - deg < -180) theta += 360;
        while (theta - deg > 180) theta -= 360;
        if (abs(theta) > 2)
            rotateTo(theta); // math checks out
    }
    int t = 4;
    // while ((xdist * xdist + ydist * ydist).convert(1_in*1_in) > minDistEpsilon * minDistEpsilon && t--) {
    //     dist_t xdist = x*1_in - chassis->getOdometry()->getState().x;
    //     dist_t ydist = y*1_in - chassis->getOdometry()->getState().y;
        moveRev((-okapi::sqrt(xdist*xdist + ydist*ydist) + delta*1_in).convert(1_in), velocity, stop);
    // }
}

const int defaultDelta2 = 8;
const int defaultDelta1 = 18;
void goToGoal(Pos p, bool twoStep = false, double goalDelta2 = defaultDelta2, double goalDelta1 = defaultDelta1)
{
    double x = p.first;
    double y = p.second;
    if (twoStep) {
        moveTo(x, y, goalDelta1, mxV1, false);
        moveTo(x, y, goalDelta2, mxV2);
    } else {
        moveTo(x, y, goalDelta2, mxV2);
    }
}
void goToGoalRev(Pos p, bool twoStep = false, double goalDelta2 = defaultDelta2, double goalDelta1 = defaultDelta1)
{
    double x = p.first;
    double y = p.second;
    if (twoStep) {
        moveToRev(x, y, goalDelta1, mxV1, false);
        moveToRev(x, y, goalDelta2, mxV2);
    } else {
        moveToRev(x, y, goalDelta2, mxV2);
    }
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
