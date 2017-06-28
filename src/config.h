#pragma once
#include <iostream>

#include <boost/filesystem.hpp>

#include "definitions.h"


class Config {
private:
	struct configState { //Stores the name and value of each individual config (e.g. width, fpsLimit)
		std::string name;
		int value;
	};

public:
	struct configSettings {
		configState width;
		configState height;
		configState fpsLimit;
	};
	internal_ void readConfigFile();

private:
	internal_ bool checkIfCfgFileExists();
};