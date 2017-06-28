#include "global.h"

SDL_Window* Global::window = 0; //TODO: Inspect if the window really needs to be global or not
SDL_Renderer* Global::renderer = 0;
SDL_Texture* Global::texture = 0;

const std::string Global::logFolder = "logs"; //TODO: This might not be needed
const std::string Global::logFile = logFolder + "/latest.log";
const std::string Global::configFolder = "cfg";
const std::string Global::customConfigFile = configFolder + "/settings.cfg";
const std::string Global::defaultConfigFile = configFolder + "/default.cfg";

const std::string Global::gameName = "Unknown Pong";

bool Global::gameCommands[MAX_GAMECOMMANDS] = {};