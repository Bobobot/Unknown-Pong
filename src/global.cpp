#include "global.h"

SDL_Window* Global::window = 0; //TODO: Inspect if the window really needs to be global or not
SDL_Renderer* Global::renderer = 0;
SDL_Texture* Global::texture = 0;
std::ofstream Global::logFileStream;

const std::string Global::logFolder = "logs";
const std::string Global::logFile = logFolder + "/latest.log";

bool Global::gameCommands[MAX_GAMECOMMANDS] = {};