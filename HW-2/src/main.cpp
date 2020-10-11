#include <string>
#include "BaseLogger.hpp"
#include "FileLogger.hpp"
#include "StderrLogger.hpp"
#include "StdoutLogger.hpp"

int main() {

    std::string log_path = "logfile.log";
    
    log::StdoutLogger coutLogger(log::Level::WARNING);
    coutLogger.debug("cout debug message");
    coutLogger.info("cout info message");
    coutLogger.warn("cout warn message");
    coutLogger.error("cout error message");

	log::StderrLogger cerrLogger(log::Level::INFO);
    cerrLogger.debug("cerr debug message");
    cerrLogger.info("cerr info message");
    cerrLogger.warn("cerr warn message");
    cerrLogger.error("cerr error message");

    log::FileLogger fileLogger;
    fileLogger.debug("file debug message");
    fileLogger.info("file info message");
    fileLogger.warn("file warn message");
    fileLogger.error("file error message");

    return 0;
}
