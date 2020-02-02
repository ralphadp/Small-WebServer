/*
 * Directory.h
 *
 *  Created on: Mar 5, 2019
 *      Author: ralph
 */

#ifndef SRC_LIBRARIES_DIRECTORY_H_
#define SRC_LIBRARIES_DIRECTORY_H_

#include <stdlib.h>
#include <dirent.h> /*directory entity*/
#include <unistd.h>

#include "../libraries/Logger.h"

class Directory {
	const char* m_dir;
	char* m_path;
public:
	Directory(const char* directory);
	virtual ~Directory();

	bool exists();
	void set(const char* directory);
	const char* get();
	void get(char* completePath);
	unsigned int size();
	bool isSlashAtEndOfDir();
	unsigned int changePath(const char* path);
};

#endif /* SRC_LIBRARIES_DIRECTORY_H_ */
