#ifndef FILE_LOGGER_HPP
#define FILE_LOGGER_HPP

#include <fstream>
#include "BaseLogger.hpp"

namespace log {

    class FileLogger : public BaseLogger {
    private:
        std::ofstream log_file_;
        void log(const std::string& msg, Level log_level) override;

    public:
        explicit FileLogger() noexcept;
        explicit FileLogger(const std::string& file_path, Level log_level) noexcept;
        void flush() override;
    };

}

#endif
