#include "Logger.h"

	Logger::Logger()
	{
	}


	Logger::~Logger()
	{
	}

	void Logger::log(std::string str)
	{
		std::cout << str << std::endl;
	}

	Logger& Logger::getInstance() {
		static Logger instance;
		return instance;
	}
