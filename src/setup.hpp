#include "main.h"
#include "components/chassis.hpp"
#include "components/controller.hpp"
#include "components/lvglWrapper.hpp"

ControllerWrapper control = ControllerWrapper(pros::E_CONTROLLER_MASTER);

const port_t liftPortL = 3;
const port_t liftPortR = 4;

pros::ADIDigitalOut backLift('E');
okapi::MotorGroup left({
    okapi::Motor(10, true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees),
    okapi::Motor(20, true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees),
});
okapi::MotorGroup right({
    okapi::Motor(1, false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees),
    okapi::Motor(11, false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees),
});

okapi::MotorGroup lift({
    okapi::Motor(liftPortL, false, okapi::AbstractMotor::gearset::red, okapi::AbstractMotor::encoderUnits::degrees),
    okapi::Motor(liftPortR, true, okapi::AbstractMotor::gearset::red, okapi::AbstractMotor::encoderUnits::degrees)
});
okapi::Motor claw(2, false, okapi::AbstractMotor::gearset::red, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor roller(8, true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
pros::Imu imu(6);

std::shared_ptr<okapi::OdomChassisController> chassis;

const int liftVoltage = 4000;
const int liftVelocity = 100;
const int rollerVelocity = 107;

const int backLiftVelocity = 20;

double liftLowPos = 15;
double liftMidPos = 50;
double liftHighPos = 750;

double clawLowPos = 0;
double clawHighPos = -210;

// double clawLowPos = 180 ;
// double clawHighPos = 30 ;

const double chassisGearRatio = 60.0/84.0;
// const double chassisGearRatio = 84.0/60.0;

// const double liftDelta = 610 - 15;
// const double liftHighPos = 410;

void clawClamp()
{
    claw.moveAbsolute(clawHighPos, 80);
}

void clawRelease()
{
    claw.moveAbsolute(clawLowPos, 80);
}

void calibrateMotorAngle(okapi::AbstractMotor &motor, double &lowPos, double &highPos, int voltage = -2500)
{
    double lastPos = INFINITY;

    while (abs(motor.getPosition() - lastPos) > 5)
    {
        lastPos = motor.getPosition();
        motor.moveVoltage(voltage);
        pros::delay(100);
    }
    lastPos = motor.getPosition();
    lowPos += lastPos;
    highPos += lastPos;
    motor.moveVelocity(0);
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    using namespace okapi;
    lift.tarePosition();

    // left.setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);
    // right.setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);
    lift.setBrakeMode(AbstractMotor::brakeMode::hold);
    // claw.setVoltageLimit(1000);

    chassis =
        ChassisControllerBuilder()
        .withMotors(left, right)
        /* set gearset, wheel diam and wheel track */
        .withDimensions(AbstractMotor::gearset::green, {{4_in, 34.5_cm}, imev5GreenTPR * chassisGearRatio})
        .withSensors(
            ADIEncoder{'G','H', true}, // left encoder
            ADIEncoder{'A','B', true} // right encoder
        )
        /* specify the tracking wheels diameter (2.75 in), track (7 in), and TPR (360) */
        /* specify the middle encoder distance (1 in) and diameter (2.75 in) */
        .withOdometry({{2.75_in, 8_in}, quadEncoderTPR})
        // .withGains(
        //     // {kp, ki, kd}
        //     {0.001, 0, 0},// distance controller gains
        //     {0.001, 0, 0} // turn controller gains
        //     // {0.001, 0, 0.0001}  // angle controller gains (helps drive straight)
        // )
        // .withClosedLoopControllerTimeUtil(50, 5, 2000_ms)
        .buildOdometry();

    // chassis =
    //     ChassisControllerBuilder()
    //     .withMotors(left, right)
    //     /* set gearset, wheel diam and wheel track */
    //     .withDimensions(AbstractMotor::gearset::green, {{4_in, 34.9_cm}, imev5GreenTPR * chassisGearRatio})
    //     .withOdometry()
    //     .withMaxVelocity(80)
    //     // .withGains(
    //     //     // {kp, ki, kd}
    //     //     {0.005, 0, 0},// distance controller gains
    //     //     {0.005, 0, 0}, // turn controller gains
    //     //     {0, 0, 0}  // angle controller gains (helps drive straight)
    //     // )
    //     // .withClosedLoopControllerTimeUtil(50, 5, 250_ms)
    //     .buildOdometry();

    // left.setReversed(false);
    // right.setReversed(true);
    // chassis =
    //     ChassisControllerBuilder()
    //     .withMotors(left, right)
    //     /* set gearset, wheel diam and wheel track */
    //     .withDimensions(AbstractMotor::gearset::green, {{4_in, 14_in}, imev5GreenTPR})
    //     /* specify the tracking wheels diameter (2.75 in), track (7 in), and TPR (360) */
    //     /* specify the middle encoder distance (1 in) and diameter (2.75 in) */
    //     .withSensors(
    //         ADIEncoder{'G','H'}, // left encoder
    //         ADIEncoder('A', 'B', true), // right encoder
    //         ADIEncoder{'C','D'}  // mid encoder
    //     )
    //     .withOdometry({{2.75_in, 7_in, 1_in, 2.75_in}, quadEncoderTPR})
    //     // .withOdometry()
    //     .withMaxVelocity(60)
    //     .buildOdometry();
}