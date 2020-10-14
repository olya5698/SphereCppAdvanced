#ifndef LEVEL_HPP
#define LEVEL_HPP

namespace log {

	enum class Level {
	    DEBUG,
	    INFO,
	    WARNING,
	    ERROR
	};

	const char* get_level(Level& log_level);

}

#endif
