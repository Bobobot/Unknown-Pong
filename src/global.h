#pragma once
#include <iostream>
#include <fstream>

#include <SDL2\SDL.h>

#include "definitions.h"


class Global {
public:
	global_variable SDL_Window* window;
	global_variable SDL_Renderer* renderer;
	global_variable SDL_Texture* texture;
	global_variable std::ofstream logFileStream;

	global_variable const std::string logFolder;
	global_variable const std::string logFile;

	global_variable bool gameCommands[MAX_GAMECOMMANDS]; //This array contains what game commands the user is inputting currently
};