#include <stdio.h>
#include <cstdint>
#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>
#include <boost/filesystem.hpp>

#define internal static
#define local_persist static
#define global_variable static

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

#define MILLISECONDS_IN_A_SECOND 1000

//Enum to store all possible actions the player could take.
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

enum logEnums {
	LOG_FILE,
	LOG_CONSOLE,
	LOG_BOTH
};

global_variable SDL_Window* globalWindow = 0; //TODO: Inspect if the window really needs to be global or not
global_variable SDL_Renderer* globalRenderer = 0;
global_variable SDL_Texture* globalTexture = 0;
global_variable std::ofstream globalLogFileStream;

global_variable const std::string globalLogFolder = "logs";
global_variable const std::string globalLogFile = globalLogFolder + "/latest.log";

global_variable bool gameCommands[MAX_GAMECOMMANDS] = {}; //This array contains what game commands the user is inputting currently

//Safely handles the closing of the whole program
internal void close() {
	SDL_DestroyWindow(globalWindow);
	SDL_Quit();
}

//Returns the current date in a format that's favorable for logging.
internal std::string timeStamp() {
	time_t currentTime = time(0);
	tm timeStruct;
	localtime_s(&timeStruct, &currentTime);
	std::stringstream timeString;
	timeString << (timeStruct.tm_year + 1900)
		<< "-"
		<< (timeStruct.tm_mon + 1)
		<< "-"
		<< (timeStruct.tm_mday)
		<< "-"
		<< (timeStruct.tm_hour)
		<< ":"
		<< (timeStruct.tm_min)
		<< ":"
		<< (timeStruct.tm_sec);
	return timeString.str();
}



//TODO: Implement in-game console
internal void logToConsole(std::string text) {
	std::cout << timeStamp() << " " << text << std::endl;
}

internal bool logToFile(std::string text) {
	bool success = true;
	globalLogFileStream.open(globalLogFile, std::ios::app);
	if (globalLogFileStream.is_open()) {
		globalLogFileStream << timeStamp() << " " << text << std::endl;
		globalLogFileStream.close();
		success = true;
	} else {
		logToConsole("Error while writing to the log file");
		success = false;
	}
	return success;
}


internal void gameLog(std::string text, int whereToLog) {
	switch (whereToLog) {
		case LOG_CONSOLE:
			logToConsole(text);
			break;
		case LOG_FILE:
			logToFile(text);
			break;
		case LOG_BOTH:
			logToConsole(text);
			logToFile(text);
			break;
	}
}

//Helps cut down on frantical copy-pasting of code. Keyboard manufacturers hate him!
internal void logErrorSDL(std::string text) {
	std::stringstream SDLtext;
	SDLtext << text << std::endl << "SDL Error: SDL_GetError()" << std::endl;
	gameLog(SDLtext.str(), LOG_BOTH);
}

//TODO: FIX
internal void clearLogFile() {
	globalLogFileStream.open(globalLogFile, std::ios::trunc);
	globalLogFileStream.close();

}

//Initializes SDL and handles all errors
internal bool initSDL(std::string title, int width, int height) {
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

internal uint32 timerCallbackSDL(uint32 interval, void *param) {
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
	if (SDL_AddTimer(fpsDelay, timerCallbackSDL, (int32 *)TIMER_FPS) == 0) {
		logErrorSDL("Error while creating the FPS timer!");
	}
}

//TODO: Customizable controls
internal void handleKeyboardInput(const uint8* keyboardState) {
	if (keyboardState[SDL_SCANCODE_UP]) {
		gameCommands[GAMECOMMAND_UP] = 1;
		gameLog("up", LOG_BOTH); //Temporary debug call
	} else {
		gameCommands[GAMECOMMAND_UP] = 0;
	}
	if (keyboardState[SDL_SCANCODE_DOWN]) {
		gameCommands[GAMECOMMAND_DOWN] = 1;
	} else {
		gameCommands[GAMECOMMAND_DOWN] = 0;
	}
	if (keyboardState[SDL_SCANCODE_SPACE]) {
		gameCommands[GAMECOMMAND_ACTION] = 1;
	} else {
		gameCommands[GAMECOMMAND_ACTION] = 0;
	}
}

internal bool createFolder(std::string folderName) {
	const boost::filesystem::path folderPath(folderName);
	return boost::filesystem::create_directory(folderPath);
}

internal void initFolders() {
	std::string path = globalLogFolder;
	boost::filesystem::path logsFolderPath(globalLogFolder);
	if (!(boost::filesystem::exists(logsFolderPath))) {
		if (!createFolder(globalLogFolder)) {
			gameLog("Failed to create folder!", LOG_CONSOLE);
		}
	}
}

int main(int argc, char* args[]) {

	bool isGameRunning = true;

	//TODO: Read in these values from a file
	std::string gameTitle = "Unknown Pong";
	int windowWidth = 800;
	int windowHeight = 600;
	int fpsLimit = 144;

	initSDL(gameTitle, windowWidth, windowHeight);
	initFolders();
	clearLogFile();
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