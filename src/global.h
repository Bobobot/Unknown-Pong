#pragma once
#include <iostream>
#include <fstream>

#include <SDL.h>

#include "definitions.h"
#include "config.h"

class Global {
public:
	global_variable SDL_Window* window;
	global_variable SDL_Renderer* renderer;
	global_variable SDL_Texture* texture;
	global_variable Config::configSettings config; //A global struct to store the contents of the config file

	
	global_variable const std::string logFolder;
	global_variable const std::string logFile;
	global_variable const std::string configFolder;
	global_variable const std::string customConfigFile; //A file holding the user-defined config values.
	global_variable const std::string defaultConfigFile; //A file holding the default config values. The program generates the customConfigFile using the defaultConfigFile in case the former does not exist yet.

	global_variable const std::string gameName;

	global_variable bool gameCommands[MAX_GAMECOMMANDS]; //This array contains what game commands the user is inputting currently
};
