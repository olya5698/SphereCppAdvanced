#include "StdoutLogger.hpp"
#include "Level.hpp"

namespace log {

	StdoutLogger::StdoutLogger(Level log_level) noexcept
	    : BaseLogger(log_level) {}

	void StdoutLogger::flush() {
	    std::cout.flush();
	}

	void StdoutLogger::log(const std::string& msg, Level log_level) {
	    print_log_by_level(msg, log_level, std::cout);
	}

}
