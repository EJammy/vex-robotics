#include "main.h"
#include "components/chassis.hpp"
#include "components/controller.hpp"
#include "components/lvglWrapper.hpp"

const port_t liftPortL = 16;
const port_t liftPortR = 17;

okapi::MotorGroup left({
    okapi::Motor(3, true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees),
    okapi::Motor(20, true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees),
});
okapi::MotorGroup right({
    okapi::Motor(2, false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees),
    okapi::Motor(11, false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees),
});

okapi::MotorGroup lift({
    okapi::Motor(liftPortL, false, okapi::AbstractMotor::gearset::red, okapi::AbstractMotor::encoderUnits::degrees),
    okapi::Motor(liftPortR, true, okapi::AbstractMotor::gearset::red, okapi::AbstractMotor::encoderUnits::degrees)
});
okapi::Motor claw(5, false, okapi::AbstractMotor::gearset::red, okapi::AbstractMotor::encoderUnits::degrees);
pros::Imu imu(6);

std::shared_ptr<okapi::OdomChassisController> chassis;

const int liftVoltage = 4000;
const int liftVelocity = 100;

double liftLowPos = 35;
double liftHighPos = 615;

double clawLowPos = -120;
double clawHighPos = -800;

const double chassisGearRatio = 60.0/84.0;

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

    // left.setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);
    // right.setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);
    lift.setBrakeMode(AbstractMotor::brakeMode::hold);

    // chassis =
    //     ChassisControllerBuilder()
    //     .withMotors(left, right)
    //     /* set gearset, wheel diam and wheel track */
    //     .withDimensions({AbstractMotor::gearset::green, chassisGearRatio}, {{4_in, 35_cm}, imev5GreenTPR})
    //     // .withSensors(
    //     //     ADIEncoder{'C','D'}, // left encoder
    //     //     ADIEncoder{'E','F'}, // right encoder
    //     //     ADIEncoder{'A','B'}  // mid encoder
    //     // )
    //     /* specify the tracking wheels diameter (2.75 in), track (7 in), and TPR (360) */
    //     /* specify the middle encoder distance (1 in) and diameter (2.75 in) */
    //     .withOdometry({{2.75_in, 7_in, 1_in, 2.75_in}, quadEncoderTPR})
    //     .buildOdometry();
}