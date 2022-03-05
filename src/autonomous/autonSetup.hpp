#ifndef autonSetup
#define autonSetup

#include "../setup.hpp"
using namespace okapi::literals;
using pros::delay;
const double matSize = 23.4166; // distance of a mat on field

// 16.8/2 = 8.4
const double robotSize = 16.8;
const double rsHalf = robotSize/2;

using Pos = std::pair<double, double>;
Pos operator+(Pos a, Pos b) {
    return Pos{a.first + b.first, a.second + b.second};
}
const Pos goalL = {3*matSize, 1.5*matSize};
const Pos goalM = {3*matSize, 3*matSize};
const Pos goalR = {3*matSize, 4.5*matSize};
const Pos goalAlliance = {1.5*matSize, 5.5*matSize}; // the goal on awp
const Pos goalAlliance2 = {matSize / 2 - 1, matSize * 1.75}; // the goal near platform

const Pos goalEnemy = {4.5*matSize, 0.5*matSize};
const Pos goalEnemy2 = {5.5*matSize + 1, 4.25 * matSize };

double mxV1 = 180; // normal velocity
double mxV2 = 65; // velocity when grabbing goal
const double circumfrence = 4*PI;
const int move_t_extra = 80;

double PERR = 2;

double curX = 0;
double curY = 0;

std::pair<double, double> getPos() {
    // return {gps.get_status().y * 39.3701 + 3 * matSize, -gps.get_status().x * 39.3701 + 3 * matSize};
    auto g = gps.get_status();
    // return {-g.x * 39.3701 + 3*matSize, g.y * 39.3701 + 3 * matSize};
    return {g.x * 39.3701 + 3*matSize, -g.y * 39.3701 + 3 * matSize};
}

void updPos(const int rep = 2) {
    // return;
    double tx = 0;
    double ty = 0;
    delay(30);
    for (int i = 0; i < rep; i++) {
        auto [x, y] = getPos();
        tx += x;
        ty += y;
        cout << x / matSize << ' ' << y / matSize << endl;
        delay(30);
    }
    cout << "====" << endl;

    std::tie(curX, curY) = Pos{tx / rep, ty / rep};
    cout << curX / matSize << ' ' << curY  / matSize<< endl;
    cout << endl;
    // delay(8000);
}

void moveFwd(double dist, double velocity = mxV1, double posErr = PERR) {
    dist = dist/circumfrence*360;
    left.moveRelative(dist, velocity);
    right.moveRelative(dist, velocity);
    delay(100);
    int t = 0;

    int time = 0;
    double degPerSec = velocity / 60.0 * 360;
    int timeout = abs(dist/degPerSec*1000);
    timeout += 1000;
    cout << "moving " << left.getPositionError() << ' ' << right.getPositionError() << endl;
    while (t < 6 && time < timeout / 12) {
        if (abs(left.getPositionError()) < posErr && abs(right.getPositionError() < posErr)) t++;
        else t = 0;
        if (time % 40 == 0) {
            // cout << "D: " << imu.get_rotation() << endl;
            // cout << "-P: " << left.getPosition() << ' ' << left.getTargetPosition() << endl;
            // cout << "-1: " << left.getPositionError() << ' ' << leftPos << endl;
            // cout << endl;
        }
        time++;
        delay(12);
    }
    if (time < timeout / 12) {
        cout << "> done ";
        cout << "-P: " << left.getPositionError() << ' ' << right.getPositionError() << endl;
    } else {
        cout << "> bad ";
        cout << "-P: " << left.getPositionError() << ' ' << right.getPositionError() << endl;
    }
}

void rotateTo(double targetAngle, double diff = 0.2) {
    if (abs(targetAngle - imu.get_rotation()) < diff*5) return;
    cout << "rotating" << endl;
    PID tpid = PID(0.07, 0.0012, 0.6, 4, 0.15); // to do: tune pid
    int t = 0;
    tpid.setTarget(targetAngle);
    while (t < 8) {
        tpid.update(imu.get_rotation());
        double force = clamp(tpid.getOutput(), 1);

        force *= 12000;
        left.moveVoltage(force);
        right.moveVoltage(-force);

        textField.setText( "R " + std::to_string(tpid.error) + " " + 
            std::to_string(tpid.iLim)+ " " + std::to_string(tpid.iStop)+ " " + std::to_string(tpid.integral)
            + " " + std::to_string( abs(tpid.error) < tpid.iLim && abs(tpid.error) > tpid.iStop ));

        if (abs(tpid.error) < diff) t++;
        else t = 0;

        // if (abs(tpid.error) < diff * 2) cout << tpid.error << endl;
        pros::delay(4);
    }
    left.moveVoltage(0);
    right.moveVoltage(0);
}

void rotateToR(double d) {
    double deg = 0;
    while (d - deg < 0) d += 360;
    rotateTo(d);
}

void rotateToL(double d) {
    double deg = 0;
    while (d - deg > 0) d -= 360;
    rotateTo(d);
}

const double minDistEpsilon = 2;
void setState(double x, double y, double deg) {
    curX = x;
    curY = y;
    imu.set_rotation(deg);
}

void setState(double deg) {
    imu.set_rotation(deg);
    updPos();
}

void rotateToPt(double x, double y, bool rev = false) {
    double dx = x-curX;
    double dy = y-curY;
    if (dy == 0) dy = 0.001;
    double theta = okapi::atan((dx / dy) * 1_in / 1_in).convert(1_deg);

    if ( (!rev && dy < 0) || (rev && dy > 0) ) theta += 180;
    theta = 90 - theta;
    double deg = imu.get_rotation();
    while (theta - deg < -180) theta += 360;
    while (theta - deg > 180) theta -= 360;

    // if (abs(theta - deg) > 2)
    rotateTo(theta); // math checks out
}

template<class T>
int sg(T x) { return x < 0 ? -1:1; }

bool doNxtUpd = true;
void moveTo(double x, double y, bool rev = false, double delta = 0.0, double velocity = mxV1, double posErr = PERR)
{
    cout << curX/matSize << ' ' << curY /matSize<< endl;
    cout << x/matSize << ' ' << y /matSize<< endl;
    double dx = x-curX;
    double dy = y-curY;
    double dist = sqrt(dx * dx + dy * dy);
    if (dist - delta < minDistEpsilon)
        return;
    rotateToPt(x, y, rev);

    curX = x - delta / dist * dx;
    curY = y - delta / dist * dy;
    moveFwd((rev?-1:1)*(sqrt(dx*dx+dy*dy) - delta), velocity, posErr);
    // if (doNxtUpd)
    //     updPos();
    // else doNxtUpd = true;
}

const int GDelta1 = 0;
const int GDelta2 = 12;
void goToGoal(Pos p, bool rev = false, double velocity = mxV2, double goalDelta1 = GDelta1)
{
    double x = p.first;
    double y = p.second;
    moveTo(x, y, rev, goalDelta1, mxV2);
}

void goToGoalT(Pos p, bool rev = false, double dist1 = GDelta1, double dist2 = GDelta2, double v1 = mxV1, double v2 = 60) {
    double x = p.first;
    double y = p.second;
    moveTo(x, y, rev, dist2, v1, 120);
    moveTo(x, y, rev, dist1, v2);
}

// void goToGoal2step(Pos p, bool rev = false)

// void clearLine()
// {
//     moveToRev(1.5*matSize, 5*matSize - rsHalf);
//     clawReleaseSync();
//     moveToRev(matSize, 5*matSize - rsHalf);

//     goToGoalRev(goalAlliance, false, 5, 20);
//     roller.moveRelative(1000, rollerVelocity);
//     delay(2000);
// }
#endif

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
