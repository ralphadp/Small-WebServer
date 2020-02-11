/*
 * filesHandler.cpp
 *
 *  Created on: Jan 10, 2019
 *      Author: ralph
 */

#include "filesHandler.h"

FilesHandler::FilesHandler(const char* mainDirectoryPath) {
	mainDirectory = new Directory(mainDirectoryPath);
}

FilesHandler::~FilesHandler() {
	if (mainDirectory) {
		delete mainDirectory;
	}
}

bool FilesHandler::getData(const char* requestedFilename, char* data, InternalDirectory::DirectoryType type) {
	int index = 0;
	Filename* filename = new Filename(requestedFilename);
	FileAssembler* fileContainer = new FileAssembler(mainDirectory, filename);
	File* temporal = new File(fileContainer);

	while (directories.get(type, index) != NULL) {
		mainDirectory->changePath(directories.get(type, index++));

		if (!mainDirectory->exists()) {
			continue;
		}

		if (temporal->open(FileAction::Type::READ)) {
			temporal->readContents(data);
			delete fileContainer;
			delete temporal;
			delete filename;

			return true;
		}
		temporal->close();
	}
	delete fileContainer;
	delete temporal;
	delete filename;

	return false;
}

void FilesHandler::setParentPathDirectory(const char* directory) {

}
