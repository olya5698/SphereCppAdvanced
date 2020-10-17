#include "BaseLogger.hpp"
#include "FileLogger.hpp"
#include "StderrLogger.hpp"
#include "StdoutLogger.hpp"
#include "Logger.hpp"
#include "LoggerFunctions.hpp"
#include "Level.hpp"

#include <iostream>
#include <string>
#include <exception>

void BaseLoggerExample() {
    std::string log_path = "logfile.log";
    
    log::StdoutLogger cout_logger(log::Level::WARNING);
    cout_logger.debug("cout debug message");
    cout_logger.info("cout info message");
    cout_logger.warn("cout warn message");
    cout_logger.error("cout error message");

    log::StderrLogger cerr_logger(log::Level::INFO);
    cerr_logger.debug("cerr debug message");
    cerr_logger.info("cerr info message");
    cerr_logger.warn("cerr warn message");
    cerr_logger.error("cerr error message");

    log::FileLogger file_logger;
    file_logger.debug("file debug message");
    file_logger.info("file info message");
    file_logger.warn("file warn message");
    file_logger.error("file error message");
}

void AdvancedLoggerExample() {
    try {
        log::init_with_stdout_logger(log::Level::WARNING);
    }
    catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
    }

    log::debug("advanced cout debug message");
    log::info("advanced cout info message");
    log::warn("advanced cout warn message");
    log::error("advanced cout error message");

    log::StderrLogger cerr_logger;
    cerr_logger.set_level(log::Level::DEBUG);
    cerr_logger.debug("Попадет в лог");
    cerr_logger.warn("Попадет в лог");
     
    cerr_logger.set_level(log::Level::WARNING);
    cerr_logger.info("Не попадет в лог");
    cerr_logger.error("Попадет в лог");

    try {
        log::init_with_file_logger("logfile.log", log::Level::ERROR);
    }
    catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
    }
    
    log::error("advanced file error message");

}

int main() {
    BaseLoggerExample();
    std::cout << std::endl;
    AdvancedLoggerExample(); 
    return 0;
}
