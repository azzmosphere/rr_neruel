#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <iostream>
#include <cstdarg>

using namespace std;

class Logger {
    public:
        static inline void info(string m) {
            cout << "INFO: " << m << endl;
        }

        static inline void error(string m) {
            cout << "ERROR: " << m << endl;
        }
};

#endif