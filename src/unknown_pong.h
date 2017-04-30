#pragma once

#include <stdio.h>
#include <string>

#include <SDL2/SDL.h>

#include "logger.h"
#include "global.h"
#include "filesystem_handler.h"
#include "input_handler.h"
#include "definitions.h"

#define MILLISECONDS_IN_A_SECOND 1000

enum timerParam {
	TIMER_FPS,
	TIMER_TICKS
};

class Unknown_pong {
public:
	internal_method bool initSDL(std::string, int, int);
	internal_method void close();
	internal_method uint32 timerCallbackSDL(uint32 interval, void * param);
	internal_method void initTimers(int fpsLimit);
	internal_method int start();
};