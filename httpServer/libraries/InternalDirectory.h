/*
 * InternalDirectory.h
 *
 *  Created on: Mar 9, 2019
 *      Author: ralph
 */

#ifndef SRC_LIBRARIES_INTERNALDIRECTORY_H_
#define SRC_LIBRARIES_INTERNALDIRECTORY_H_

#include <stdio.h>

class InternalDirectory {
public:
	enum DirectoyType {
		JSON = 0,
		XML,
		HTML,
		YML,
		UNKNOWN
	};
private:
	const char** directoriesList[UNKNOWN + 1];
	const unsigned int XML_DIR_MAX = 1;
	const unsigned int JSON_DIR_MAX = 2;
	const unsigned int YML_DIR_MAX = 1;
	const unsigned int HTML_DIR_MAX = 1;
public:
	InternalDirectory();
	~InternalDirectory();

	void loadDirectories();
	void unloadloadDirectories();
	const char* get(DirectoyType type, unsigned int index);
};

#endif /* SRC_LIBRARIES_INTERNALDIRECTORY_H_ */
