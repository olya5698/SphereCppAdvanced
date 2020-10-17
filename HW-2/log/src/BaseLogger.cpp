#include "BaseLogger.hpp"

namespace log {

	BaseLogger::BaseLogger() noexcept : level_(Level::INFO) {}

	BaseLogger::BaseLogger(Level log_level) noexcept : level_(log_level) {}

	void BaseLogger::debug(const std::string& msg) {
	    log(msg, Level::DEBUG);
	}

	void BaseLogger::info(const std::string& msg) {
	    log(msg, Level::INFO);
	}

	void BaseLogger::warn(const std::string& msg) {
	    log(msg, Level::WARNING);
	}

	void BaseLogger::error(const std::string& msg) {
	    log(msg, Level::ERROR);
	}

	void BaseLogger::set_level(Level log_level) {
	    level_ = log_level;
	}

	Level BaseLogger::level() const {
	    return level_;
	}

	void BaseLogger::print_log_by_level(const std::string& msg, Level log_level, std::ostream& out) {
		if (log_level >= level()) {
	    	out << (log::get_level(log_level)) << msg.c_str() << std::endl;
	    }
	}

}
