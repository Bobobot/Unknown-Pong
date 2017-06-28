#include "config.h"

#include "global.h"
#include "logger.h"

internal_ std::ofstream cfgFileStream;
internal_ std::ifstream defaultCfgFileStream;

void Config::readConfigFile() {
	defaultCfgFileStream.open(Global::defaultConfigFile);
	if (defaultCfgFileStream.is_open()) {

	} else {
		Logger::gameLog("Failed to open config file stream!", LOG_BOTH);
	}
}

//Checks the existance of the config file, and generates a new one using the default config file if it's missing.
bool Config::checkIfCfgFileExists() {
	bool exists = true;
	if (boost::filesystem::exists(Global::customConfigFile)) {
		exists = true;
		return exists;
	} else {
		//TODO: Don't just simply copy-paste the two files
		cfgFileStream.open(Global::customConfigFile);
		char tempChar; //Using char instead of int8 because the size of char can vary
		while (!defaultCfgFileStream.eof()) {
			defaultCfgFileStream.get(tempChar);
			cfgFileStream << tempChar;
		}
	}
}