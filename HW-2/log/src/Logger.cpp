#include "Logger.hpp"
#include "StderrLogger.hpp"
#include <stdexcept> 

namespace log {

	Logger::Logger() : global_logger_(std::make_unique<StderrLogger>()) {}

	Logger& Logger::get_instance() noexcept {
	    static Logger log_inst;
	    return log_inst;
	}

	BaseLogger& Logger::get_global_logger() const noexcept {
	    return *global_logger_;
	}

	void Logger::set_global_logger(BaseLoggerPtr base_log_ptr) {
	    if (base_log_ptr) {
	        global_logger_ = std::move(base_log_ptr);
	    } else {
	        throw std::runtime_error("Bad pointer to BaseLogger");
	    }
	}

}
