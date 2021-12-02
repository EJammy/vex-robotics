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
const Pos goalAlliance = {1.5*matSize, 5.5*matSize};

const double mxV1 = 140;
const double mxV2 = 40;

void clawClampSync()
{
    clawClamp();
    delay(500);
}

void clawReleaseSync()
{
    clawRelease();
    delay(500);
}

// void moveTo(double x, double y)
// {
//     chassis->driveToPoint({x*1_in, y*1_in});
// }

void autonWait(double ms, double err) {
    // while (!chassis->isSettled()) {
    //     delay(200);
    //     cout<<left.getPosition()<<' '<<right.getPosition()<<'\n';
    //     cout<<left.getTargetPosition()<<' '<<right.getTargetPosition()<<'\n';
    //     cout<<left.getPositionError()<<' '<<right.getPositionError()<<endl;
    //     cout<<"==="<<endl;
    // }
    // return;

    int t = 0;
    int x = 0;
    while (t < ms) {
        if (x % 20 == 0) {
            cout<<left.getPosition()<<' '<<right.getPosition()<<'\n';
            cout<<left.getTargetPosition()<<' '<<right.getTargetPosition()<<'\n';
            cout<<left.getPositionError()<<' '<<right.getPositionError()<<endl;
            cout<<abs(left.getPositionError()) + abs(right.getPositionError())<<endl;
            cout<<"==="<<endl;
        }
        x++;
        if  (abs(left.getPositionError()) <= err || abs(right.getPositionError()) <= err) {
            t++;
        } else {
            t = 0;
        }
        delay(80);
    }
}

void wait1() { autonWait(2, 30); }
void wait2() { autonWait(1, 200); }

void moveToRev(double x, double y, double delta = 0.0, bool wait = true) // x-axis is vertical axis
{
    dist_t xdist = x*1_in;
    dist_t ydist = y*1_in;
    xdist = chassis->getOdometry()->getState().x - xdist;
    ydist = chassis->getOdometry()->getState().y - ydist;

    if (ydist != 0_m)
    {
        auto theta = okapi::atan((xdist / ydist));
        if (ydist < 0_in) theta += 180_deg;
        chassis->turnToAngle(90_deg - theta); // math checks out
    }
    chassis->moveDistanceAsync(-okapi::sqrt(xdist*xdist + ydist*ydist) + delta*1_in);
    if (wait) {
        wait1();
    }
}

void rotateTo(double deg)
{
    chassis->turnAngle(deg*1_deg);
}


void moveTo(double x, double y, double delta = 0.0, bool wait = true)
{
    dist_t xdist = x*1_in;
    dist_t ydist = y*1_in;
    xdist = chassis->getOdometry()->getState().x - xdist;
    ydist = chassis->getOdometry()->getState().y - ydist;

    if (ydist != 0_m)
    {
        auto theta = okapi::atan((xdist / ydist));
        if (ydist > 0_in) theta += 180_deg;
        chassis->turnToAngle(90_deg - theta); // math checks out
    }
    chassis->moveDistanceAsync(okapi::sqrt(xdist*xdist + ydist*ydist) - delta*1_in);
    if (wait) wait1();
}

const double goalDelta1 = 20;
const double goalDelta2 = 10;

void goToGoal(Pos p, bool twoStep = true)
{
    double x = p.first;
    double y = p.second;
    if (twoStep) {
        moveTo(x, y, goalDelta1, false);
        wait2();
    }
    chassis->setMaxVelocity(mxV2);
    moveTo(x, y, goalDelta2, false);
    wait1();

    chassis->setMaxVelocity(mxV1);
}

void goToGoalRev(Pos p, bool twoStep = true)
{
    double x = p.first;
    double y = p.second;
    if (twoStep) {
        moveToRev(x, y, goalDelta1, false);
        wait2();
    }
    chassis->setMaxVelocity(mxV2);
    moveToRev(x, y, goalDelta2, false);
    wait1();

    chassis->setMaxVelocity(mxV1);
}

// void moveForward(double x)
// {
// 	PID pid = PID(0.016, 0.00045, 0.1, 9, 0.15);
//     int t = 0;
//     pid.setTarget(x);
//     while (t < 8)
//     {
//         pid.update()
//     }
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
