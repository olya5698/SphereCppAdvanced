#include <iostream>

#include "StderrLogger.hpp"

namespace log {

	StderrLogger::StderrLogger(Level log_level) noexcept
	    : BaseLogger(log_level) {}

	void StderrLogger::flush() {}

	void StderrLogger::log(const std::string& msg, Level log_level) {
	    if (log_level >= level()) {
	        std::cerr << (log::print_level(log_level)) << msg.c_str() << std::endl;
	    }
	}

}
