#include "main.h"
#include "components/controller.hpp"
#include "components/lvglWrapper.hpp"
#include "lift.hpp"
#include "clamp.hpp"

lvText textField(20, 20, lv_scr_act(), "Foo");

ControllerWrapper control = ControllerWrapper(pros::E_CONTROLLER_MASTER);

Clamp frontClamp('A');
Clamp backClamp('B');
okapi::MotorGroup right({
    okapi::Motor(1, true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees),
    okapi::Motor(10, true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees),
});
okapi::MotorGroup left({
    okapi::Motor(2, false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees),
    okapi::Motor(9, false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees),
});

/* back lift */
Lift backLift(
    okapi::Motor(3, false, okapi::AbstractMotor::gearset::red, okapi::AbstractMotor::encoderUnits::degrees),
    {80, 300, 990}
);

Lift mainLift(
    okapi::Motor(4, false, okapi::AbstractMotor::gearset::red, okapi::AbstractMotor::encoderUnits::degrees),
    {0, 300, 960}
);

/* front low lift */
Lift lowLift(
    okapi::Motor(5, false, okapi::AbstractMotor::gearset::red, okapi::AbstractMotor::encoderUnits::degrees),
    {-500,-300, 0},
    200,
    2
);

okapi::Motor roller(7, true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
pros::Imu imu(8);

const int liftVoltage = 4000;
const int liftVelocity = 100;
const int rollerVelocity = 88;

const int backLiftVelocity = 20;

double clawLowPos = 0;
double clawHighPos = -210;

// double clawLowPos = 180 ;
// double clawHighPos = 30 ;

// const double chassisGearRatio = 60.0/84.0;
const double chassisGearRatio = 1;
// const double chassisGearRatio = 84.0/60.0;

// const double liftDelta = 610 - 15;
// const double liftHighPos = 410;

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    using namespace okapi;

    left.setBrakeMode(AbstractMotor::brakeMode::brake);
    right.setBrakeMode(AbstractMotor::brakeMode::brake);
    // claw.setVoltageLimit(1000);
}