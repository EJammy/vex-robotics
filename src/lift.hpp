#include "main.h"
using pros::delay;

/**
 * A lift class.
 *
 * @see Lift()
 */
class Lift : public okapi::Motor
{
    double liftVelocity;
    size_t cur;
    bool moving = false;

    public:

        /**
         * A list of positions
         */
        const std::vector<double> pos;

        /**
         * # The lift
         *
         * Construct a "Lift" which is a wrapper around okapi::Motor.
         * A lift has multiple standard positions which the motor ought to
         * stay in.
         *
         * @param motor the okapi::Motor to control
         * @param positions the list of positions
         * @param velocity the velocity in which the motor should move in
         * @parem initPos the initial position
         * @see set pos
         */
        Lift(okapi::Motor motor, std::initializer_list<double> positions, double velocity = 200, int initPos = 0) :
            okapi::Motor(motor), pos(positions), liftVelocity(velocity), cur(initPos)
        {
            tarePosition();
            setBrakeMode(AbstractMotor::brakeMode::hold);
        }

        /**
         * Get the position
         *
         * @return the current position index
         */
        size_t getPos() { return cur; }

        /**
         * Set the poition
         *
         * Example:
         * ```cpp
         *     Lift lift(motor, [1, 2, 3]);
         *     lift.set(1);
         * ```
         *
         */
        void set(int x) {
            cur = x;
            cur = std::min(cur, pos.size()-1);
            moving = true;
            moveAbsolute(pos[cur], liftVelocity);
        }

        /**
         * Move to position x + delta degrees
         *
         * @param x the position
         * @param delta an offset from the position
         */
        void move(int x, int delta) {
            moveAbsolute(pos[x] + delta, liftVelocity);
        }

        /// A plus-plus operator
        ///
        /// Very good
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

        /**
         * Drives the Lift.
         *
         * Usually run in driver control loop in a frame by frame fashion
         *
         * @param up Whether to go up or not. Usually
         */
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
