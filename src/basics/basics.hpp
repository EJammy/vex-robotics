
#ifndef _BASICS_HPP
#define _BASICS_HPP

#include <iostream>
#include <sstream>
#include "pid.hpp"
#include "okapi/api.hpp"

using std::cout;
using std::endl;
using std::uint8_t;
using dist_t = okapi::QLength;
using port_t = uint8_t;
using sonic_t = pros::ADIUltrasonic;

// const double PI = acos(-1);
std::pair<double,double> rotate(double x, double y, double deg){
	deg = deg*PI/180;
	return std::make_pair(x*cos(deg)-y*sin(deg), x*sin(deg) + y * cos(deg));
}

/**
 * make abs(num) = bound when abs(num) > bound
 */
double clamp(double num, double bound){
	return std::max(std::min(num, bound), -bound);
}

double lerp(double xmin, double xmax, double ymin, double ymax, double x) {
	return ymin + (x - xmin) * (ymax - ymin) / (xmax - xmin);
}

std::string toStr(double a, int precision = 5){
	std::ostringstream oss;
	oss.precision(precision);
	oss<<a;
	return oss.str();
}
double inchTomm(double x){
	return x * 25.4;
}
double mmToInch(double x){
	return x / 25.4;
}
double inchToDeg(double x){
	return x * 360/(3.25*PI);
}
double degToInch(double deg){
	return deg * 3.25*PI / 360.0;
}
#endif //_BASICS_HPP
