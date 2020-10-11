#include "FileLogger.hpp"

namespace log {

	FileLogger::FileLogger() noexcept : log_file_("logfile.log") {}

	FileLogger::FileLogger(const std::string& file_path, Level log_level) noexcept
	    : log_file_(file_path), BaseLogger(log_level) {}

	void FileLogger::flush() {
	    log_file_.flush();
	}

	void FileLogger::log(const std::string& msg, Level log_level) {
	    if (log_level >= level()) {
	        log_file_ << (log::print_level(log_level)) << msg.c_str() << std::endl;
	    }
	}

}
