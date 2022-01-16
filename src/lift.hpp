#include "main.h"

class Lift : public okapi::Motor
{
    double low;
    double high;
    double liftVelocity;
    bool cur = 1; // low pos -> false, high pos -> true
    public:
        Lift(okapi::Motor motor, double lowLim = -999, double highLim = 999, double velocity = 100) :
            okapi::Motor(motor), low(lowLim), high(highLim), liftVelocity(velocity)
        {
            tarePosition();
            setBrakeMode(AbstractMotor::brakeMode::hold);
        }

        void flip() {
            cur = !cur;
            if (cur) moveAbsolute(high, liftVelocity);
            else moveAbsolute(low, liftVelocity);
        }

        void drive(bool up, bool down) {
            // cout<<up<<' '<<down<<'\n';
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
};

class LiftV2 : public okapi::Motor
{
    double liftVelocity;
    std::vector<double> pos;
    size_t cur = 0;
    public:
        LiftV2(okapi::Motor motor, std::initializer_list<double> positions, double velocity = 100) :
            okapi::Motor(motor), pos(positions), liftVelocity(velocity)
        {
            tarePosition();
            setBrakeMode(AbstractMotor::brakeMode::hold);
        }

        void set(int x) {
            cur = x;
            cur = std::min(cur, pos.size()-1);
            moveAbsolute(pos[cur], liftVelocity);
        }

        void operator++(int) {
            set(cur+1);
        }
        void operator--(int) {
            if (cur > 0) set(cur-1);
        }
        void flip() {
            if (cur = 0) set(1);
            else set(0);
        }

        void drive(bool up, bool down) {
            // cout<<up<<' '<<down<<'\n';
            double high = pos.back();
            double low = pos.front();
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
};