#pragma once
#include <string>

#include <boost/filesystem.hpp>

#include "logger.h"
#include "global.h"
#include "definitions.h"

class FilesystemHandler {
public:
	internal_method bool createFolder(std::string folderName);
	internal_method void initFolders();
};