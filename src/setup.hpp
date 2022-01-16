#include "main.h"
#include "components/controller.hpp"
#include "components/lvglWrapper.hpp"
#include "lift.hpp"
#include "clamp.hpp"


ControllerWrapper control = ControllerWrapper(pros::E_CONTROLLER_MASTER);

Clamp clamp1('A');
Clamp clamp2('B');
okapi::MotorGroup right({
    okapi::Motor(1, true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees),
    okapi::Motor(10, true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees),
});
okapi::MotorGroup left({
    okapi::Motor(2, false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees),
    okapi::Motor(9, false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees),
});

/* front lift */
Lift lift1(
    okapi::Motor(3, false, okapi::AbstractMotor::gearset::red, okapi::AbstractMotor::encoderUnits::degrees),
    80,
    990
);

Lift lift2(
    okapi::Motor(4, false, okapi::AbstractMotor::gearset::red, okapi::AbstractMotor::encoderUnits::degrees),
    80,
    960
);
/* back low lift */
LiftV2 lift3(
    okapi::Motor(5, false, okapi::AbstractMotor::gearset::red, okapi::AbstractMotor::encoderUnits::degrees),
    {-500,-300, 0}
);

okapi::Motor roller(7, true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
pros::Imu imu(6);

std::shared_ptr<okapi::OdomChassisController> chassis;

const int liftVoltage = 4000;
const int liftVelocity = 100;
const int rollerVelocity = 95;

const int backLiftVelocity = 20;

double liftLowPos = 15;
double liftMidPos = 50;
double liftHighPos = 750;

double clawLowPos = 0;
double clawHighPos = -210;

// double clawLowPos = 180 ;
// double clawHighPos = 30 ;

// const double chassisGearRatio = 60.0/84.0;
const double chassisGearRatio = 1;
// const double chassisGearRatio = 84.0/60.0;

// const double liftDelta = 610 - 15;
// const double liftHighPos = 410;

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

    // left.setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);
    // right.setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);
    left.setBrakeMode(AbstractMotor::brakeMode::brake);
    right.setBrakeMode(AbstractMotor::brakeMode::brake);
    // claw.setVoltageLimit(1000);

    chassis =
        ChassisControllerBuilder()
        .withMotors(left, right)
        /* set gearset, wheel diam and wheel track */
        .withDimensions(AbstractMotor::gearset::green, {{4_in, 15_in}, imev5GreenTPR * chassisGearRatio})
        /* specify the tracking wheels diameter (2.75 in), track (7 in), and TPR (360) */
        .withOdometry()
        .withGains(
            // {kp, ki, kd}
            {0.001, 0, 0},// distance controller gains
            {0.002, 0, 0} // turn controller gains
            // {0.001, 0, 0.0001}  // angle controller gains (helps drive straight)
        )
        // .withClosedLoopControllerTimeUtil(50, 5, 2000_ms)
        .buildOdometry();
}