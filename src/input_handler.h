#pragma once
#include "global.h"
#include "logger.h"
#include "definitions.h"

class InputHandler {
public:
	internal_method void handleKeyboardInput(const uint8* keyboardState);
};