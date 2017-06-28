#include "logger.h"

internal_ std::ofstream logFileStream;

//Returns the current date in a format that's favorable for logging.
std::string Logger::timeStamp() {
	time_t currentTime = time(0);
	tm timeStruct;
#if (defined(WIN32)  || defined(_WIN32) ||defined (__WIN32__))
	localtime_s(&timeStruct, &currentTime);
#else
	localtime_r(&currentTime, &timeStruct);
#endif
	std::stringstream timeString;
	timeString << (timeStruct.tm_year + 1900)
		<< "-"
		<< (timeStruct.tm_mon + 1)
		<< "-"
		<< (timeStruct.tm_mday)
		<< "-"
		<< (timeStruct.tm_hour)
		<< ":"
		<< (timeStruct.tm_min)
		<< ":"
		<< (timeStruct.tm_sec);
	return timeString.str();
}

//TODO: Implement in-game console
void Logger::logToConsole(std::string text) {
	std::cout << timeStamp() << " " << text << std::endl;
}

 bool Logger::logToFile(std::string text) {
	bool success = true;
	logFileStream.open(Global::logFile, std::ios::app);
	if (logFileStream.is_open()) {
		logFileStream << timeStamp() << " " << text << std::endl;
		logFileStream.close();
		success = true;
	} else {
		logToConsole("Error while writing to the log file");
		success = false;
	}
	return success;
}

 //Logs a string into the console and/or the log file
void Logger::gameLog(std::string text, int whereToLog) {
	switch (whereToLog) {
		case LOG_CONSOLE:
			logToConsole(text);
			break;
		case LOG_FILE:
			logToFile(text);
			break;
		case LOG_BOTH:
			logToConsole(text);
			logToFile(text);
			break;
	}
}

//Helps cut down on frantical copy-pasting of code. Keyboard manufacturers hate him!
void Logger::logErrorSDL(std::string text) {
	std::stringstream SDLtext;
	SDLtext << text << std::endl << "SDL Error: SDL_GetError()" << std::endl;
	gameLog(SDLtext.str(), LOG_BOTH);
}


void Logger::clearLogFile() {
	logFileStream.open(Global::logFile, std::ios::trunc);
	logFileStream.close();

}