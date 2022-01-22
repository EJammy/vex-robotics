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


void moveFwd(double dist, double velocity = mxV1) {
    dist = dist/circumfrence*360;
    left.moveRelative(dist, velocity);
    right.moveRelative(dist, velocity);
    delay(100);
    int t = 0;

    const int posErr = 5;
    while (t < 12) {
        if (abs(left.getPositionError()) < posErr && abs(right.getPositionError() < posErr)) t++;
        else t = 0;
        delay(12);
    }
}

void rotateTo(double targetAngle, double diff = 0.2) {
    PID tpid = PID(0.025, 0.0005, 0.0, 8, 0.15);
    int t = 0;
    tpid.setTarget(targetAngle);
    while (t < 12) {
        tpid.update(imu.get_rotation());
        double force = clamp(tpid.getOutput(), 1);

        force *= 12000;
        left.moveVoltage(force);
        right.moveVoltage(-force);

        textField.setText( "R " + std::to_string(tpid.error) + " " + 
            std::to_string(tpid.iLim)+ " " + std::to_string(tpid.iStop)+ " " + std::to_string(tpid.integral)
            + " " + std::to_string( abs(tpid.error) < tpid.iLim && abs(tpid.error) > tpid.iStop ));

        if (abs(tpid.error) < diff) t++;
        else t = 0;
        pros::delay(4);
    }
    pros::delay(20);
}

void rotateToR(double d) {
    double deg = 0;
    while (d - deg < 0) d += 360;
    rotateTo(d);
}

void rotateToL(double d) {
    double deg = 0;
    while (d - deg > 0) d -= 360;
    rotateTo(d);
}

const double minDistEpsilon = 2;
double curX = 0;
double curY = 0;
void setState(double x, double y, double deg) {
    curX = x;
    curY = y;
    imu.set_rotation(deg);
}
void moveTo(double x, double y, bool rev = false, double delta = 0.0, double velocity = mxV1)
{
    double dx = x-curX;
    double dy = y-curY;
    curX = x;
    curY = y;
    if (dx * dx + dy * dy < minDistEpsilon * minDistEpsilon)
        return;

    double deg = 0;
    if (dy != 0)
    {
        auto theta = atan(dx / dy);
        if ( (!rev && dy < 0) || (rev && dy > 0)) theta += 180;
        theta = 90 - theta;
        while (theta - deg < -180) theta += 360;
        while (theta - deg > 180) theta -= 360;
        if (abs(theta) > 2)
            rotateTo(theta); // math checks out
    }
    moveFwd((rev?-1:1)*(sqrt(dx*dx+dy*dy) - delta), velocity);
}

const int defaultDelta2 = 8;
const int defaultDelta1 = 18;
void goToGoal(Pos p, double goalDelta2 = defaultDelta2, double goalDelta1 = defaultDelta1)
{
    double x = p.first;
    double y = p.second;
    moveTo(x, y, false, goalDelta2, mxV2);
}

void goToGoalRev(Pos p, double goalDelta2 = defaultDelta2, double goalDelta1 = defaultDelta1)
{
    double x = p.first;
    double y = p.second;
    moveTo(x, y, true, goalDelta2, mxV2);
}



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
