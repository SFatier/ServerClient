#pragma once

#include <string>
#include <iostream>


class Logger
{
public:
	void log(std::string);
	static Logger& getInstance();
private:
	Logger();
	~Logger();
};