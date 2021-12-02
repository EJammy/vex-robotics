#include "autonomous.hpp"

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}


/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {

	ControllerWrapper control = ControllerWrapper(pros::E_CONTROLLER_MASTER);
	// lvButton guiButton(screenX-20, screenY-20, 100, 100, 0, lv_color_hex(0xFFFFFF), lv_scr_act());
	lvText textField(20, 20, lv_scr_act(), "Foo");

	int t = 0;
	int liftMode = 1;
	int delta = 0;
	while (true) {
		if (t % 100 == 0)
			// cout<<control.L_X()<<endl;
		t++;

		// chassis.driveVoltage(control.L_Y(), control.L_X()*0.7);
		left.moveVoltage((control.L_Y() + control.R_X()*0.7)*12000);
		right.moveVoltage((control.L_Y() - control.R_X()*0.7)*12000);

		if (control.L1())
		{
			clawClamp();
		}
		else if (control.L2())
		{
			clawRelease();
		}
		else if (control.A())
		{
			claw.moveVoltage(6000);
		}
		if (control.LEFT())
		{
			liftLowPos = -INFINITY;
			lift.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
		}
		// if (control.B())
		// {
		// 	lift.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
		// }

		if (control.X())
		{
			autonomous();
		}

		if (control.R1() && lift.getPosition() < liftHighPos-5)
		{
			lift.moveVelocity(liftVelocity);
			liftMode = 1;
		}
		else if (control.R2() && lift.getPosition() > liftLowPos+5)
		{
			lift.moveVelocity(-liftVelocity);
			liftMode = 1;
		}
		else if (liftMode == 1)
		{
			if (lift.getPosition() > liftHighPos)
				lift.moveAbsolute(liftHighPos, liftVelocity);
			else if (lift.getPosition() < liftLowPos)
				lift.moveAbsolute(liftLowPos, liftVelocity);
			else
				lift.moveVelocity(0);
		}
		// if (lift.getPosition() < liftLowPos)
		// {
		// 	lift.moveAbsolute(liftLowPos, liftVelocity);
		// }
		// if (lift.getPosition() > liftHighPos)
		// {
		// 	lift.moveAbsolute(liftHighPos, liftVelocity);
		// }

		// if (control.L1())
		// {
		// 	lift.moveAbsolute(liftHighPos, liftVelocity);
		// 	liftMode = 0;
		// }
		// else if (control.L2())
		// {
		// 	lift.moveAbsolute(liftLowPos, liftVelocity);
		// 	liftMode = 0;
		// }

		// if (control.UP())
		// {
		// 	if (t % 25 == 0)
		// 	{
		// 		liftLowPos++;
		// 		liftHighPos++;
		// 	}
		// }
		// if (control.DOWN())
		// {
		// 	if (t % 25 == 0)
		// 	{
		// 		liftLowPos--;
		// 		liftHighPos--;
		// 	}
		// }

		if (control.DOWN())
		{
			backLift.set_value(true);
		}
		else if (control.UP())
		{
			backLift.set_value(false);
		}

		// textField.setText(std::to_string(lift.getPosition()));
		textField.setText(
			toStr(chassis->getOdometry()->getState().x.convert(1_in)) + " " +
			toStr(chassis->getOdometry()->getState().y.convert(1_in)) + " " +
			toStr(chassis->getOdometry()->getState().theta.convert(1_deg)) + "\n" +
			toStr(control.L1()) + " " + toStr(control.L2()) + " " + toStr(control.A()) + "\n"
			);
		if (t % 100) {
			cout<<
				toStr(chassis->getOdometry()->getState().x.convert(1_in)) + " " +
				toStr(chassis->getOdometry()->getState().y.convert(1_in)) + " " +
				toStr(chassis->getOdometry()->getState().theta.convert(1_deg))
			<<endl; 
		}
		pros::delay(4);
	}
}
