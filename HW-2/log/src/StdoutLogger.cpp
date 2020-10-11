#include <iostream>

#include "StdoutLogger.hpp"
#include "Level.hpp"

namespace log {

	StdoutLogger::StdoutLogger(Level log_level) noexcept
	    : BaseLogger(log_level) {}

	void StdoutLogger::flush() {
	    std::cout.flush();
	}

	void StdoutLogger::log(const std::string& msg, Level log_level) {
	    if (log_level >= level()) {
	    	std::cout << (log::print_level(log_level)) << msg.c_str() << std::endl;
	    }
	}

}
