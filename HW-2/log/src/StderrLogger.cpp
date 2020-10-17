#include <iostream>
#include "StderrLogger.hpp"

namespace log {

	StderrLogger::StderrLogger(Level log_level) noexcept
	    : BaseLogger(log_level) {}

	void StderrLogger::flush() {}

	void StderrLogger::log(const std::string& msg, Level log_level) {
	    print_log_by_level(msg, log_level, std::cerr);
	}

}
