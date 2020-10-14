#ifndef STDOUT_LOGGER_HPP
#define STDOUT_LOGGER_HPP

#include "BaseLogger.hpp"

namespace log {

	class StdoutLogger : public BaseLogger {
	private:
	    void log(const std::string& msg, Level log_level) override;
	
	public:
	    explicit StdoutLogger() = default;
	    explicit StdoutLogger(Level log_level) noexcept;
	    void flush() override;
	};

}

#endif
