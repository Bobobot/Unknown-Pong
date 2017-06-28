#include "filesystem_handler.h"


//Checks the existance of the specified folder, and creates a new one in case it's missing
void FsHandler::createFolder(std::string folderName) {
	const boost::filesystem::path folderPath(folderName);
	if (!(boost::filesystem::exists(folderPath))) {
		if (!(boost::filesystem::create_directory(folderPath))) {
			Logger::gameLog("Failed to create the " + folderName + "folder!", LOG_CONSOLE);
		}
	}
}

//Creates must-have folders if they don't exist already
void FsHandler::initFolders() {
	createFolder(Global::logFolder);
}
