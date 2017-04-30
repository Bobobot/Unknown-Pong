#pragma once
#include <stdio.h>
#include <string>
#include <sstream>
#include <ctime>

#include "global.h"
#include "definitions.h"

class Logger {
public:
	internal_method void gameLog(std::string text, int whereToLog);
	internal_method void clearLogFile();
	internal_method void logErrorSDL(std::string text);
private:
	internal_method std::string timeStamp();
	internal_method void logToConsole(std::string text);
	internal_method bool logToFile(std::string text);
};