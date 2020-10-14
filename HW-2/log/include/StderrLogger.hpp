#ifndef STDERR_LOGGER_HPP
#define STDERR_LOGGER_HPP

#include "BaseLogger.hpp"

namespace log {

	class StderrLogger : public BaseLogger {
	private:
	    void log(const std::string& msg, Level log_level) override;

	public:
	    explicit StderrLogger() = default;
	    explicit StderrLogger(Level log_level) noexcept;
	    void flush() override;
	};

}

#endif
