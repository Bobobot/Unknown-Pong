#include <stdio.h>
#include <cstdint>
#include <SDL2/SDL.h>
#include <string>

#define internal static
#define local_persist static
#define global_variable static

#define uint8 uint8_t  
#define uint16 uint16_t 
#define uint32 uint32_t 
#define uint64 uint64_t 

#define int8 int8_t 
#define int16 int16_t
#define int32 int32_t
#define int64 int64_t

#define MILLISECONDS_IN_A_SECOND 1000

//Enum to store all possible actions the user could take.
enum gameCommandsEnum {
	GAMECOMMAND_UP,
	GAMECOMMAND_DOWN,
	GAMECOMMAND_ACTION, //Brings the pads closer to each other
	MAX_GAMECOMMANDS //Isn't a command by itself - is used in order to determine how many gameCommands there are 
};

enum timerParam {
	TIMER_FPS,
	TIMER_TICKS
};

global_variable SDL_Window* globalWindow = 0; //TODO: Inspect if the window really needs to be global or not
global_variable SDL_Renderer* globalRenderer = 0;
global_variable SDL_Texture* globalTexture = 0;

global_variable bool gameCommands[MAX_GAMECOMMANDS] = {}; //This array contains what game commands the user is inputting currently

//Safely handles the closing of the whole program
internal void close() {
	SDL_DestroyWindow(globalWindow);
	SDL_Quit();
}


//Helps cut down on frantical copy-pasting of code. Keyboard manufacturers hate him!
internal void logErrorSDL(std::string text) {
	printf("%s\n SDL_Error:%s\n", text.c_str(), SDL_GetError()); //TODO: Replace printf with an actual file logger
}

//Initializes SDL and handles all errors
internal bool init(std::string title, int width, int height) {
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) { //TODO: Probably will be replaced by SDL_INIT_EVERYTHING
		logErrorSDL("Failed to initialize SDL!");
		success = false;
	} else {
		globalWindow = SDL_CreateWindow(title.c_str(),
										SDL_WINDOWPOS_CENTERED,
										SDL_WINDOWPOS_CENTERED,
										width,
										height,
										0); //TODO: Add SDL_WINDOW_FULLSCREEN
		if (globalWindow == 0) {
			logErrorSDL("SDL error while creating a window!");
			success = false;
		} else {
			globalRenderer = SDL_CreateRenderer(globalWindow,
												-1,
												SDL_RENDERER_ACCELERATED);
			if (globalRenderer == 0) {
				logErrorSDL("Failed to create renderer!");
				success = false;
			} else {
				//TODO: IMG_Init in case the program will use textures as well
			}
		}
	}
	return success;
}

internal uint32 timerCallback(uint32 interval, void *param) {
	SDL_Event event;
	SDL_UserEvent userEvent = {};
	userEvent.type = SDL_USEREVENT;
	userEvent.code = (int32)param;

	event.type = SDL_USEREVENT;
	event.user = userEvent;

	SDL_PushEvent(&event);
	return interval;

}

internal void initTimers(int fpsLimit) {
	int fpsDelay = MILLISECONDS_IN_A_SECOND / fpsLimit; //The amount of milliseconds that should pass between each frame
	if (SDL_AddTimer(fpsDelay, timerCallback, (int32 *)TIMER_FPS) == 0) {
		logErrorSDL("Error while creating the FPS timer!");
	}
}

//TODO: Customizable controls
internal void handleKeyboardInput(const uint8* keyboardState) {
	if (keyboardState[SDL_SCANCODE_UP]) {
		gameCommands[GAMECOMMAND_UP] = 1;
		printf("up\n");
	} else {
		gameCommands[GAMECOMMAND_UP] = 0;
	}
	if (keyboardState[SDL_SCANCODE_DOWN]) {
		gameCommands[GAMECOMMAND_DOWN] = 1;
		printf("down\n");
	} else {
		gameCommands[GAMECOMMAND_DOWN] = 0;
	}
	if (keyboardState[SDL_SCANCODE_SPACE]) {
		gameCommands[GAMECOMMAND_ACTION] = 1;
		printf("space\n");
	} else {
		gameCommands[GAMECOMMAND_ACTION] = 0;
	}
}

int main(int argc, char* args[]) {

	bool isGameRunning = true;

	//TODO: Read in these values from a file
	std::string gameTitle = "Unknown Pong";
	int windowWidth = 800;
	int windowHeight = 600;
	int fpsLimit = 144;

	init(gameTitle, windowWidth, windowHeight);
	initTimers(fpsLimit);

	const uint8* keyboardState = SDL_GetKeyboardState(0); //Updates every time SDL_PollEvent() is called

	//This is the main game loop
	while (isGameRunning) {
		SDL_Event sdlEvent;

		while (SDL_PollEvent(&sdlEvent)) {
			switch (sdlEvent.type) {
				case SDL_USEREVENT:
					if (sdlEvent.user.code == TIMER_FPS) {
						handleKeyboardInput(keyboardState);
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