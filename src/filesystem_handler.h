#pragma once
#include <string>
#include <sys/stat.h>

#include <boost/filesystem.hpp>

#include "logger.h"
#include "global.h"
#include "definitions.h"

class FsHandler {
public:
	internal_ void createFolder(std::string folderName);
	internal_ void initFolders();

	struct files {
		std::string logFile;
	};
};