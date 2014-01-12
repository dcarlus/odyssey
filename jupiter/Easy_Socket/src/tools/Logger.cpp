#include "Logger.h"
#include <ctime>
#include <iostream>

using namespace std ;

void Logger::print(const string& log) {
    time_t now = time(0) ;
    struct tm tstruct = *localtime(&now) ;
    char buffer[80] ;
    strftime(buffer, sizeof(buffer), "%Y-%m-%d.%X", &tstruct) ;

    string printed = "[" + std::string(buffer) + "] " + log ;
    cout << printed << endl ;
}
