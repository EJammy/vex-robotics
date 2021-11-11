#include "main.h"

/**
 * wrapper class for pros::Controller
 * shorter digital input
 * analog range [-100, 100] instead of [-127, 127]
 */
class ControllerWrapper: public pros::Controller{
	private:
	public:
		ControllerWrapper(pros::controller_id_e_t id): pros::Controller(id){}
		bool L1(){
			return get_digital(DIGITAL_L1);
		}
		bool L2(){
			return get_digital(DIGITAL_L2);
		}
		bool R1(){
			return get_digital(DIGITAL_R1);
		}
		bool R2(){
			return get_digital(DIGITAL_R2);
		}
		bool A(){
			return get_digital(DIGITAL_A);
		}
		bool B(){
			return get_digital(DIGITAL_B);
		}
		bool X(){
			return get_digital(DIGITAL_X);
		}
		bool Y(){
			return get_digital(DIGITAL_Y);
		}
		bool UP(){
			return get_digital(DIGITAL_UP);
		}
		bool DOWN(){
			return get_digital(DIGITAL_DOWN);
		}
		bool LEFT(){
			return get_digital(DIGITAL_LEFT);
		}
		bool RIGHT(){
			return get_digital(DIGITAL_RIGHT);
		}
		double L_Y(){
			return get_analog(ANALOG_LEFT_Y) / 127.0;
		}
		double L_X(){
			return get_analog(ANALOG_LEFT_X) / 127.0;
		}
		double R_Y(){
			return get_analog(ANALOG_RIGHT_Y) / 127.0;
		}
		double R_X(){
			return get_analog(ANALOG_RIGHT_X) / 127.0;
		}
};