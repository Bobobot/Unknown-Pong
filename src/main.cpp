#include <stdio.h>
#include <cstdint>
#include "SDL.h"
#include <string>

#define internal static
#define local_persist static
#define global_variable static

#define uint8_t  uint8
#define uint16_t uint16
#define uint32_t uint32
#define uint64_t uint64

#define int8_t int8
#define int16_t int16
#define int32_t int32
#define int64_t int64

global_variable SDL_Window* globalWindow = 0; //TODO: Inspect if the window really needs to be global or not
global_variable SDL_Renderer* globalRenderer = 0;
global_variable SDL_Texture* globalTexture = 0;

internal void close() { //Safely handles the closing of the whole program
	SDL_DestroyWindow(globalWindow);
	SDL_Quit();
}

internal void logErrorSDL(std::string text) { //Helps cut down on frantical copy-pasting of code. Keyboard manufacturers hate him!
	printf("%s\n SDL_Error:%s\n", text.c_str(), SDL_GetError());
}

internal bool init(std::string title, int width, int height) { //Initializes SDL and handles all errors
	//TODO: initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) { //TODO: Probably will be replaced by SDL_INIT_EVERYTHING
		logErrorSDL("Failed to initialize SDL!");
	} else {
		globalWindow = SDL_CreateWindow(title.c_str(),
										SDL_WINDOWPOS_CENTERED,
										SDL_WINDOWPOS_CENTERED,
										width,
										height,
										0); //TODO: Add SDL_WINDOW_FULLSCREEN
		if (globalWindow == 0) {
			logErrorSDL("SDL error while creating a window!");
		} else {
			globalRenderer = SDL_CreateRenderer(globalWindow,
												-1,
												SDL_RENDERER_ACCELERATED);
			if (globalRenderer == 0) {
				logErrorSDL("Failed to create renderer!");
			} else {
				//TODO: IMG_Init in case the program will use textures as well
			}
		} 
	}
}


int main(int argc, char* args[]) {
	bool isGameRunning = true;

	//TODO: Read in these values from a file
	std::string gameTitle = "Unknown Pong";
	int windowWidth = 800;
	int windowHeight = 600;

	while (isGameRunning) { //This is the main game loop

	}

	close();
	return 0;
}