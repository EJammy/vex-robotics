#include "setup.hpp"
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

using namespace okapi::literals;
using pros::delay;
const double matSize = 23.42; // distance of a mat on field

void moveForward(double x)
{
    chassis->setState({0_in, 0_in, 0_deg});
    chassis->driveToPoint({x*1_in, 0_in});
}

void moveTo(okapi::Point p)
{
    chassis->driveToPoint(p);
}

void rotateTo(double deg)
{
    chassis->turnAngle(deg*1_deg);
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

// void moveForward(double x)
// {
//     left.moveRelative(x/(4*PI) * 360 * chassisGearRatio, 100);
//     right.moveRelative(x/(4*PI) * 360 * chassisGearRatio, 100);
//     delay(5000);
//     // while (!left.isStopped() || !right.isStopped())
//     // {
//     //     delay(10);
//     // }
// }

void turn(double x)
{
    chassis->setState({0_in, 0_in, 0_deg});
    chassis->turnAngle(x*1_deg);
}


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

void autonomous() {
    // right.moveRelative(360,40);
    // delay(10000);
    // moveForward(matSize);
    // delay(5000);
    // claw.moveAbsolute(-600, 80);
    // delay(1000);
    // claw.moveAbsolute(clawLowPos, 80);
    // delay(1000);
    // claw.moveAbsolute(clawHighPos, 80);
    // delay(1000);

    clawClamp();
    delay(1000);
    clawRelease();
    delay(1000);
    // lift.moveAbsolute(liftLowPos+60, liftVelocity);
    // delay(1000);
    moveForward(-10);
    delay(1000);

    // moveForward(50);

    // clawClamp();
    // delay(1000);
    // lift.moveAbsolute(liftLowPos+60, liftVelocity);
    // delay(1000);

    // moveForward(-50);
    // delay(5000);
}