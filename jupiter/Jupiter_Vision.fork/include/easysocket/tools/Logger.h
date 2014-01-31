#ifndef __EASYSOCKET_LOGGER_H__
#define __EASYSOCKET_LOGGER_H__

#include <string>

/**
 * @brief A simple logger to display logs during the execution.
 * @version 1.0     08/07/2013
 * @author  Denis CARLUS
 */
class Logger {
    public:
        /**
         * @brief Print a log on screen.
         * @param log   The log to print.
         */
        static void print(const std::string& log) ;
} ;

#endif
