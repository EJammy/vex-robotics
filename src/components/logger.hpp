#include "../basics/basics.hpp"
#include <fstream>

/**
 * Logging stuff
 * 
 * WIP, To be tested
 * 
 * Consider Okapi logger
 * 
 */

void log(std::string str){
	std::ofstream logOut("ChangeUpLog.txt", std::ofstream::out | std::ofstream::app);
	logOut<<str<<endl;
	logOut.close();
	cout<<pros::millis()<<": "<<str<<endl;
}