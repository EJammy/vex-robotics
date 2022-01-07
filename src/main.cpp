#include "autonomous.hpp"

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}




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
    // cout<< autonSelection << endl;
			// competition_initialize();
			// autonomous();

	// lvButton guiButton(screenX-20, screenY-20, 100, 100, 0, lv_color_hex(0xFFFFFF), lv_scr_act());
	lvText textField(20, 20, lv_scr_act(), "Foo");

	int t = 0;
	int liftMode = 1;
	int delta = 0;
	while (true) {
		// if (t % 100 == 0) cout<<control.L_X()<<endl;
		t++;

		// chassis.driveVoltage(control.L_Y(), control.L_X()*0.7);
		left.moveVoltage((control.L_Y() + control.R_X()*0.7)*12000);
		right.moveVoltage((control.L_Y() - control.R_X()*0.7)*12000);
		// if (control.L_Y() > 0) {
		// 	roller.moveVelocity(rollerVelocity);
		// } else {
		// 	roller.moveVoltage(0);
		// }
		if (control.Y()) {
			autonomous();
		}

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
			lift1.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
		}
		// if (control.B())
		// {
		// 	lift1.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
		// }


		if (control.R1() && lift1.getPosition() < liftHighPos-5)
		{
			lift1.moveVelocity(liftVelocity);
			liftMode = 1;
		}
		else if (control.R2() && lift1.getPosition() > liftLowPos+5)
		{
			lift1.moveVelocity(-liftVelocity);
			liftMode = 1;
		}
		else if (liftMode == 1)
		{
			if (lift1.getPosition() > liftHighPos)
				lift1.moveAbsolute(liftHighPos, liftVelocity);
			else if (lift1.getPosition() < liftLowPos)
				lift1.moveAbsolute(liftLowPos, liftVelocity);
			else
				lift1.moveVelocity(0);
		}
		// if (lift1.getPosition() < liftLowPos)
		// {
		// 	lift1.moveAbsolute(liftLowPos, liftVelocity);
		// }
		// if (lift1.getPosition() > liftHighPos)
		// {
		// 	lift1.moveAbsolute(liftHighPos, liftVelocity);
		// }

		// if (control.L1())
		// {
		// 	lift1.moveAbsolute(liftHighPos, liftVelocity);
		// 	liftMode = 0;
		// }
		// else if (control.L2())
		// {
		// 	lift1.moveAbsolute(liftLowPos, liftVelocity);
		// 	liftMode = 0;
		// }

		if (control.X())
		{
			if (t % 12 == 0)
			{
				liftLowPos++;
				liftHighPos++;
			}
		}
		if (control.B())
		{
			if (t % 12 == 0)
			{
				liftLowPos--;
				liftHighPos--;
			}
		}

		if (control.DOWN())
		{
			clamp1.set_value(true);
		}
		else if (control.UP())
		{
			clamp1.set_value(false);
		}

		// textField.setText(std::to_string(lift1.getPosition()));
		textField.setText(
			toStr(chassis->getOdometry()->getState().x.convert(1_in)) + " " +
			toStr(chassis->getOdometry()->getState().y.convert(1_in)) + " " +
			toStr(chassis->getOdometry()->getState().theta.convert(1_deg)) + "\n" +
			toStr(control.L1()) + " " + toStr(control.L2()) + " " + toStr(control.A()) + "\n"
			);
		if (t % 100 == 0) {
			cout<<
				toStr(chassis->getOdometry()->getState().x.convert(1_in)) + " " +
				toStr(chassis->getOdometry()->getState().y.convert(1_in)) + " " +
				toStr(chassis->getOdometry()->getState().theta.convert(1_deg))
			<<endl; 
		}
		pros::delay(4);
	}
}
