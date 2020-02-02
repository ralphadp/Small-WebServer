/*
 * filesHandler.h
 *
 *  Created on: Jan 10, 2019
 *      Author: ralph
 */

#ifndef LIBRARIES_FILES_HANDLER_H
#define LIBRARIES_FILES_HANDLER_H

#include "file.h"
#include "FileAssembler.h"
#include "InternalDirectory.h"

/**
 * File handler class
 */
class FilesHandler
{
	Directory* mainDirectory;
	InternalDirectory directories;

public:
	FilesHandler(const char* mainDirectoryPath = ".");
	~FilesHandler();

	bool getData(const char* filename, char* data, InternalDirectory::DirectoyType type = InternalDirectory::DirectoyType::JSON);

private:
	void setParentPathDirectory(const char* directory);
};

#endif /* LIBRARIES_FILES_HANDLER_H */
