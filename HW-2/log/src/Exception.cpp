#include "Exception.hpp"

namespace log {

	LoggerException::LoggerException(const std::string& err_msg)
	    : err_msg_(err_msg) {}

	const char* LoggerException::what() const noexcept {
	    return err_msg_.c_str();
	}

}
