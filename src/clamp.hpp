#include "main.h"

class Clamp : pros::ADIDigitalOut
{
    bool f = false;
    public:
        Clamp(char port) : pros::ADIDigitalOut(port) {}

        void set(bool val) {
            f = val;
            set_value(f);
        }

        void flip() {
            set(!f);
        }

};