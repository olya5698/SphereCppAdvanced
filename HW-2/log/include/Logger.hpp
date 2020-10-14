#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <memory>
#include "BaseLogger.hpp"

namespace log {

    using BaseLoggerPtr = std::unique_ptr<BaseLogger>;

    class Logger {
    private:
        BaseLoggerPtr global_logger_;

        Logger();
        ~Logger() noexcept = default;

    public:
        static Logger& get_instance() noexcept;

        BaseLogger& get_global_logger() const noexcept;
        void set_global_logger(BaseLoggerPtr base_log_ptr);

        Logger(const Logger& other_logger) = delete;
        Logger& operator=(const Logger& other_logger) = delete;

    };

}

#endif
