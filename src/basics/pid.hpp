#include "main.h"

using std::abs; // important!! code uses abs(int) if not used

struct PID {
	double error = INFINITY;
	double target = 0;
	double integral = 0;
	double derivative = 0;
	double lastError = 0;
	const double kp;
	const double ki;
	const double kd;
	const double iLim; // integral kicks in only when abs(error) < iLim
	const double iStop; // integral resets to zero when abs(error) < iStop
	PID(double _kp, double _ki, double _kd, double _iLim, double _iStop = -1) : 
		kp(_kp), ki(_ki), kd(_kd), iLim(_iLim), iStop(_iStop)
	{}

	/* set new target and reset variables */
	void setTarget(double newTarget){
		target = newTarget;
		error = INFINITY;
		lastError = INFINITY;
		derivative = 0;
		integral = 0;
	}
	/* update variables and return output */
	double update(double reading){
		error = target - reading;
		if (lastError != INFINITY){
			derivative = error - lastError;
		}
		lastError = error;
		/* to do: figure out why std::abs is different from abs */
		if (abs(error) < iLim && abs(error) > iStop){
			integral += error;
		}else{
			integral = 0;
		}
		if ( (error < 0 && lastError > 0) || (error > 0 && lastError < 0) )
			integral = 0;
		return getOutput();
	}
	double getOutput(){
		return error * kp + derivative * kd + integral * ki;
	}
};