#include "LoggerFunctions.hpp"
#include "StdoutLogger.hpp"
#include "StderrLogger.hpp"
#include "FileLogger.hpp"

namespace log {

    void debug(const std::string& msg) {
        auto& debug_logger = Logger::get_instance().get_global_logger();
        debug_logger.debug(msg);
    }

    void info(const std::string& msg) {
        auto& info_logger = Logger::get_instance().get_global_logger();
        info_logger.info(msg);
    }

    void warn(const std::string& msg) {
        auto& warn_logger = Logger::get_instance().get_global_logger();
        warn_logger.warn(msg);
    }

    void error(const std::string& msg) {
        auto& error_logger = Logger::get_instance().get_global_logger();
        error_logger.error(msg);
    }

    void init_with_stdout_logger(Level log_level) {
        Logger::get_instance().set_global_logger(std::make_unique<StdoutLogger>(log_level));
    }

    void init_with_stderr_logger(Level log_level) {
        Logger::get_instance().set_global_logger(std::make_unique<StderrLogger>(log_level));
    }

    void init_with_file_logger(const std::string& file_path, Level log_level) {
        Logger::get_instance().set_global_logger(std::make_unique<FileLogger>(file_path, log_level));
    }

} 
