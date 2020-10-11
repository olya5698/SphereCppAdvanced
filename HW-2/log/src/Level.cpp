#include "Level.hpp"

namespace log {

	const char* print_level(Level& log_level) {
		if (log_level == log::Level::DEBUG) {
			return "DEBUG: ";
		}

		if (log_level == log::Level::INFO) {
			return "INFO: ";
		}

		if (log_level == log::Level::WARNING) {
			return "WARNING: ";
		}

		return "ERROR: ";
	}

}
