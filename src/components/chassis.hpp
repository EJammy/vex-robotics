#include "../basics/basics.hpp"


// PID -> motor ramp -> motor
class DualMotor{
	private:
		pros::Motor m1;
		pros::Motor m2;
	public:
		void move_velocity(int velocity) {
			m1.move_velocity(velocity);
			m2.move_velocity(velocity);
		}
		void move_voltage(int voltage) {
			m1.move_voltage(voltage);
			m2.move_voltage(voltage);
		}
		void set_brake_mode(pros::motor_brake_mode_e_t mode){
			m1.set_brake_mode(mode);
			m2.set_brake_mode(mode);
		}
		void set_encoder_units(pros::motor_encoder_units_e_t unit){
			m1.set_encoder_units(unit);
			m2.set_encoder_units(unit);
		}
		DualMotor(port_t p1, port_t p2, bool rev1, bool rev2): 
			m1(p1, MOTOR_GEARSET_06, rev1), 
			m2(p2, MOTOR_GEARSET_06, rev2)
		{}
};
class Chassis{
	private:
		DualMotor left;
		DualMotor right;
	public:
		Chassis(port_t l1, port_t l2, port_t r1, port_t r2): left(l1, l2, false, false), right(r1, r2, true, true)
		{
			left.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
			right.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
			left.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
			right.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
		}

		/**
		 * Drives the motor. Might not work when |force| + |offset| > 100
		 * 
		 * \param percent voltage to drive forward
		 * \param offset rotation (offsets drive two motors in different directions)
		 */
		void driveVoltage(double percent, double offset = 0){
			/* move_voltage takes range [-12000, 12000] */
			percent *= 12000.0; offset *= 12000.0;
			left.move_voltage(percent + offset);
			right.move_voltage(percent - offset);
		}

		/**
		 * Drives the motor. Might not work when |force| + |offset| > 100
		 * 
		 * \param velocity velocity to drive forward
		 * \param offset rotation (offsets drive two motors in different directions)
		 */
		void drive(double velocity, double offset = 0){
			/* move_velocity takes range [-600, 600] for 1:18 gearset */
			/* move_voltage takes range [-12000, 12000] */
			velocity *= 6.0; offset *= 6.0;
			left.move_velocity(velocity + offset);
			right.move_velocity(velocity - offset);
			// cout<<velocity<<endl;
		}


		/**
		 * max temperature among all motors
		 */
		// double maxTemp(){
		// 	double ltemp = left.get_temperature();
		// 	double rtemp = right.get_temperature();
		// 	return std::max(ltemp, rtemp);
		// }
};
