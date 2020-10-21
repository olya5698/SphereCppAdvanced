#ifndef BASE_LOGGER_HPP
#define BASE_LOGGER_HPP

#include <string>
#include <iostream>
#include <fstream>
#include "Level.hpp"

namespace log {

	class BaseLogger {
	private:
		Level level_;
	    virtual void log(const std::string& msg, Level log_level) = 0;

	public:
	    BaseLogger() noexcept;
	    explicit BaseLogger(Level log_level) noexcept;
	    virtual ~BaseLogger() = default;

	    void debug(const std::string& msg);
	    void info(const std::string& msg);
	    void warn(const std::string& msg);
	    void error(const std::string& msg);

	    void set_level(Level log_level);
	    Level level() const;
	    virtual void flush() = 0;
	    void print_log_by_level(const std::string& msg, Level log_level, std::ostream &out);
	    const char* get_level(Level& log_level);
	}; 

}

#endif 
