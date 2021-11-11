#include "main.h"

struct PID{
	double error = INFINITY;
	double target = 0;
	double integral = 0;
	double derivative = 0;
	double lastError = 0;
	double kp;
	double ki;
	double kd;
	double iLim; // integral kicks in only when abs(error) < iLim
	double iStop; // integral resets to zero when abs(error) < iStop
	PID(double _kp, double _ki, double _kd, double _iLim, double _iStop = -1){
		kp = _kp;
		ki = _ki;
		kd = _kd;
		iLim = _iLim;
		iStop = _iStop;
	}
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
		if (abs(error) < iLim && abs(error) > iStop){
			integral += error;
		}else{
			integral = 0;
		}
		return getOutput();
	}
	double getOutput(){
		return error * kp + derivative * kd + integral * ki;
	}
};