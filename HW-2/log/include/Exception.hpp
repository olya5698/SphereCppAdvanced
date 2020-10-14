#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <exception>
#include <string>

namespace log {

	class LoggerException : public std::exception {
	private:
	    std::string err_msg_;
	
	public:
	    explicit LoggerException(const std::string& err_msg);
	    const char* what() const noexcept override;
	};
}

#endif
