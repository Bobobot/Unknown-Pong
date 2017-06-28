#pragma once
#include <stdio.h>
#include <string>
#include <sstream>
#include <ctime>

#include "global.h"
#include "definitions.h"

class Logger {
public:
	internal_ void gameLog(std::string text, int whereToLog);
	internal_ void clearLogFile();
	internal_ void logErrorSDL(std::string text);
private:
	internal_ std::string timeStamp();
	internal_ void logToConsole(std::string text);
	internal_ bool logToFile(std::string text);
};