#pragma once
#include "global.h"
#include "logger.h"
#include "definitions.h"

class InputHandler {
public:
	internal_ void handleKeyboardInput(const uint8* keyboardState);
};