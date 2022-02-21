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
    selectL.hide();
    selectR.hide();
    selectWP.hide();
    // cout<< autonSelection << endl;
			// competition_initialize();
			// autonomous();

	// lvButton guiButton(screenX-20, screenY-20, 100, 100, 0, lv_color_hex(0xFFFFFF), lv_scr_act());

	int t = 0;
	int liftMode = 1;
	int delta = 0;
	while (true) {
		// if (t % 100 == 0) cout<<control.L_X()<<endl;
		t++;

		// chassis->getModel()->arcade(control.L_Y(), control.L_X()*0.7);
		if (control.LEFT()) {
			roller.moveVelocity(-rollerVelocity);
		} else if (control.L_Y() > 0 || control.X()) {
			roller.moveVelocity(rollerVelocity);
		} else {
			roller.moveVoltage(0);
		}

		left.moveVoltage((-control.L_Y() + control.R_X())*12000);
		right.moveVoltage((-control.L_Y() - control.R_X())*12000);

		if (control.A() && control.X()) {
			roller.moveVoltage(0);
			clamp1.set(0);
			clamp2.set(0);
			imu.reset();
			delay(100);
			while (imu.is_calibrating()) delay(100);
			autonomous();
		}

		backLift.drive(control.L1(), control.L2());
		mainLift.drive(control.R1(), control.R2());
		// lowLift.drive(control.UP(), control.DOWN());
		if (control.get_digital_new_press(DIGITAL_DOWN)) {
			lowLift++;
		}
		if (control.get_digital_new_press(DIGITAL_B)) {
			lowLift--;
		}

		if (control.get_digital_new_press(DIGITAL_Y))
		{
			clamp1.flip();
		}
		if (control.get_digital_new_press(DIGITAL_RIGHT))
		{
			clamp2.flip();
		}

		// lift1.drive(true, false);

//		cout<<control.R1()<<' '<<control.R2()<<'\n';

		textField.setText(std::to_string(control.R1()));


		// textField.setText(std::to_string(lift1.getPosition()));
		textField.setText(
			toStr(control.L1()) + " " + toStr(control.L2()) + " " + toStr(control.A()) + "\n"
			+ toStr(imu.get_rotation())
			);
		// if (t % 100 == 0) {
		// 	cout<<
		// 		toStr(chassis->getOdometry()->getState().x.convert(1_in)) + " " +
		// 		toStr(chassis->getOdometry()->getState().y.convert(1_in)) + " " +
		// 		toStr(chassis->getOdometry()->getState().theta.convert(1_deg))
		// 	<<endl; 
		// }
		if (control.L1() && control.L2() && control.R1() && control.R2()) {
			backLift.moveVoltage(0);
			mainLift.moveVoltage(0);
			lowLift.moveVoltage(0);

			backLift.resetPos(10000);
			mainLift.resetPos(10000);
			lowLift.resetPos(10000);
			pros::delay(2000);
		}
		pros::delay(4);
	}
}
