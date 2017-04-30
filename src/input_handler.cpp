#include "input_handler.h"

//TODO: Customizable controls
void InputHandler::handleKeyboardInput(const uint8* keyboardState) {
	if (keyboardState[SDL_SCANCODE_UP]) {
		Global::gameCommands[GAMECOMMAND_UP] = 1;
		Logger::gameLog("up", LOG_BOTH); //Temporary debug call
	} else {
		Global::gameCommands[GAMECOMMAND_UP] = 0;
	}
	if (keyboardState[SDL_SCANCODE_DOWN]) {
		Global::gameCommands[GAMECOMMAND_DOWN] = 1;
	} else {
		Global::gameCommands[GAMECOMMAND_DOWN] = 0;
	}
	if (keyboardState[SDL_SCANCODE_SPACE]) {
		Global::gameCommands[GAMECOMMAND_ACTION] = 1;
	} else {
		Global::gameCommands[GAMECOMMAND_ACTION] = 0;
	}
}