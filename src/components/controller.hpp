#include "../basics/basics.hpp"

#include <fstream>

/**
 * wrapper class for pros::Controller
 * shorter digital input
 * analog range [-100, 100] instead of [-127, 127]
 */

enum controller_mapping_t {
    cmap_lift1_up = 0,
    cmap_lift1_down,
    cmap_lift2_up,
    cmap_lift2_down,
    cmap_lift3_up,
    cmap_lift3_down,
    cmap_clamp1,
    cmap_clamp2,
	CONTROLLER_MAPPING_CNT
};

class ControllerWrapper: public pros::Controller{
	private:
	public:

		using button_t = pros::controller_digital_e_t;
		button_t list[CONTROLLER_MAPPING_CNT];

        // ControllerWrapper() {
		// 	button_t lift1_up = DIGITAL_R1;
		// 	button_t lift1_down = DIGITAL_R2;
		// 	button_t lift2_up = DIGITAL_L1;
		// 	button_t lift2_down = DIGITAL_L2;
		// 	button_t lift3_up = DIGITAL_DOWN;
		// 	button_t lift3_down = DIGITAL_B;
		// 	button_t frontClamp = DIGITAL_L1;
		// 	button_t backClamp = DIGITAL_L1;
        // }

		void init() {
			std::ifstream fin("settings.txt");
		}

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