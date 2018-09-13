#pragma once

#include <string>
#include <iostream>


class Logger
{
public:
	Logger();
	~Logger();
	static void log(std::string);
};