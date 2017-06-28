#include "unknown_pong.h"

//Initializes SDL and handles all errors
bool Unknown_pong::initSDL(std::string title, int width, int height) {
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) { //TODO: Probably will be replaced by SDL_INIT_EVERYTHING
		Logger::logErrorSDL("Failed to initialize SDL!");
		success = false;
	} else {
		Global::window = SDL_CreateWindow(title.c_str(),
										  SDL_WINDOWPOS_CENTERED,
										  SDL_WINDOWPOS_CENTERED,
										  width,
										  height,
										  0); //TODO: Add SDL_WINDOW_FULLSCREEN
		if (Global::window == 0) {
			Logger::logErrorSDL("SDL error while creating a window!");
			success = false;
		} else {
			Global::renderer = SDL_CreateRenderer(Global::window,
												  -1,
												  SDL_RENDERER_ACCELERATED);
			if (Global::renderer == 0) {
				Logger::logErrorSDL("Failed to create renderer!");
				success = false;
			} else {
				//TODO: IMG_Init in case the program will use textures as well
			}
		}
	}
	return success;
}

//Safely handles the closing of the whole program
void Unknown_pong::close() {
	SDL_DestroyWindow(Global::window);
	SDL_Quit();
}


//The event that's called by SDL's timers. It sends an SDL_USEREVENT to the message queue with a parameter attached
uint32 Unknown_pong::timerCallbackSDL(uint32 interval, void *param) {
	SDL_Event event;
	SDL_UserEvent userEvent = {};
	userEvent.type = SDL_USEREVENT;
	userEvent.code = (int32)param;

	event.type = SDL_USEREVENT;
	event.user = userEvent;

	SDL_PushEvent(&event);
	return interval;

}

//Initializes SDL timers
void Unknown_pong::initTimers(int fpsLimit) {
	int fpsDelay = MILLISECONDS_IN_A_SECOND / fpsLimit; //The amount of milliseconds that should pass between each frame
	if (SDL_AddTimer(fpsDelay, timerCallbackSDL, (int32 *)TIMER_FPS) == 0) {
		Logger::logErrorSDL("Error while creating the FPS timer!");
	}
}


int Unknown_pong::start() {

	bool isGameRunning = true;

	//TODO: Read in these values from a file
	int windowWidth = 800;
	int windowHeight = 600;
	int fpsLimit = 144;

	initSDL(Global::gameName, windowWidth, windowHeight);
	FsHandler::initFolders();
	Logger::clearLogFile();
	initTimers(fpsLimit);

	const uint8* keyboardState = SDL_GetKeyboardState(0); //Updates every time SDL_PollEvent() is called

	//This is the main game loop
	while (isGameRunning) {
		SDL_Event sdlEvent;

		while (SDL_PollEvent(&sdlEvent)) {
			switch (sdlEvent.type) {
				case SDL_USEREVENT:
					if (sdlEvent.user.code == TIMER_FPS) {
						InputHandler::handleKeyboardInput(keyboardState);
					} else if (sdlEvent.user.code == TIMER_TICKS) {
						//TODO: Implement ticks
					}
					break;
				case SDL_QUIT:
					isGameRunning = false;
					break;
			}
		}

	}

	close();
	return 0;
}

