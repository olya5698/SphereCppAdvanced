#ifndef LOGGER_FUNCTIONS_HPP
#define LOGGER_FUNCTIONS_HPP

#include <string>
#include "Logger.hpp"
#include "Level.hpp"

namespace log {

	void debug(const std::string& msg);
	void info(const std::string& msg);
	void warn(const std::string& msg);
	void error(const std::string& msg);

	void init_with_stdout_logger(Level log_level);
	void init_with_stderr_logger(Level log_level);
	void init_with_file_logger(const std::string& file_path, Level log_level);

}

#endif
