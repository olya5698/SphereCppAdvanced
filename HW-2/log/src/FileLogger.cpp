#include "FileLogger.hpp"

namespace log {

	FileLogger::FileLogger() noexcept : log_file_("logfile.log") {}

	FileLogger::FileLogger(const std::string& file_path, Level log_level) noexcept
	    : log_file_(file_path), BaseLogger(log_level) {}

	void FileLogger::flush() {
	    log_file_.flush();
	}

	void FileLogger::log(const std::string& msg, Level log_level) {
	    print_log_by_level(msg, log_level, log_file_);
	}

}
