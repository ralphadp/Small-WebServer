/*
 * InternalDirectory.cpp
 *
 *  Created on: Mar 9, 2019
 *      Author: ralph
 */

#include "InternalDirectory.h"

InternalDirectory::InternalDirectory() {
	loadDirectories();
}

InternalDirectory::~InternalDirectory() {
	unloadDirectories();
}

void InternalDirectory::loadDirectories() {
	//old issue: ** -->   <type>*[bound]
	this->directoriesList[JSON] = new const char*[JSON_DIR_MAX + 1] {
	    Global::TEMPLATE_JSON_DIRECTORY,
		"/config/json/",
		NULL
	};

	this->directoriesList[XML] = new const char*[XML_DIR_MAX + 1] {
		Global::TEMPLATE_XML_DIRECTORY,
		NULL
	};

	this->directoriesList[HTML] = new const char*[HTML_DIR_MAX + 1] {
		"/templates/html/",
		NULL
	};

	this->directoriesList[YML] = new const char*[YML_DIR_MAX + 1] {
		"/templates/yml/",
		NULL
	};

	this->directoriesList[UNKNOWN] = NULL;
}

void InternalDirectory::unloadDirectories() {
	for (unsigned int type = JSON; type < UNKNOWN; type++) {
		delete [] this->directoriesList[type];
	}
}

const char* InternalDirectory::get(DirectoryType type, unsigned int index) {
	return this->directoriesList[type][index];
}
