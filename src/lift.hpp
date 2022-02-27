#include "main.h"
using pros::delay;

class Lift : public okapi::Motor
{
    double liftVelocity;
    size_t cur;
    bool moving = false;

    public:
        const std::vector<double> pos;
        Lift(okapi::Motor motor, std::initializer_list<double> positions, double velocity = 200, int initPos = 0) :
            okapi::Motor(motor), pos(positions), liftVelocity(velocity), cur(initPos)
        {
            tarePosition();
            setBrakeMode(AbstractMotor::brakeMode::hold);
        }

        size_t getPos() { return cur; }
        void set(int x) {
            cur = x;
            cur = std::min(cur, pos.size()-1);
            moving = true;
            moveAbsolute(pos[cur], liftVelocity);
        }
        void move(int x, int delta) {
            moveAbsolute(pos[x] + delta, liftVelocity);
        }

        void operator++(int) {
            set(cur+1);
        }
        void operator--(int) {
            if (cur > 0) set(cur-1);
        }
        void flip() {
            if (cur = 0) set(pos.size()-1);
            else set(0);
        }

        void drive(bool up, bool down) {
            // cout<<up<<' '<<down<<'\n';
            double high = pos.back();
            double low = pos.front();
            if (up || down) moving = false;
            if (moving) return;
            if (up && getPosition() < high-5)
                moveVelocity(liftVelocity);
            else if (down && getPosition() > low+5)
                moveVelocity(-liftVelocity);
            else {
                if (getPosition() > high)
                    moveAbsolute(high, liftVelocity);
                else if (getPosition() < low)
                    moveAbsolute(low, liftVelocity);
                else
                    moveVelocity(0);
            }
        }

        void resetPos(int voltage) {
            if (getActualVelocity() == PROS_ERR_F) return;
            if (pos.front() >= 0) voltage *= -1;
            moveVoltage(voltage);
            delay(200);
            while (abs(getActualVelocity()) > 1) {
                delay(50);
            }
            moveVoltage(0);
            tarePosition();
        }
};