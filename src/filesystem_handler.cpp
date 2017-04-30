#include "filesystem_handler.h"

bool FilesystemHandler::createFolder(std::string folderName) {
	const boost::filesystem::path folderPath(folderName);
	return boost::filesystem::create_directory(folderPath);
}

//Creates must-have folders if they don't exist already
void FilesystemHandler::initFolders() {
	std::string path = Global::logFolder;
	boost::filesystem::path logsFolderPath(Global::logFolder);
	if (!(boost::filesystem::exists(logsFolderPath))) {
		if (!createFolder(Global::logFolder)) {
			Logger::gameLog("Failed to create folder!", LOG_CONSOLE);
		}
	}
}