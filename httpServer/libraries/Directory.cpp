/*
 * Directory.cpp
 *
 *  Created on: Mar 5, 2019
 *      Author: ralph
 */

#include "Directory.h"

/**
 * @param const char* directory set the pointer of the external directory path
 */
Directory::Directory(const char* directory) {
	m_dir = directory;
	m_path = NULL;
}

Directory::~Directory() {
	if (m_path) {
		delete [] m_path;
	}
}

bool Directory::exists() {
	//Use of Directory-entity function
	DIR* dir = opendir(m_dir);

	if (dir == NULL) {

		return false;
	}
	closedir(dir);

	return true;
}

void Directory::set(const char* directory) {
	m_dir = directory;
}

const char* Directory::get() {
	return m_dir;
}

void Directory::get(char* completePath) {
	if (m_dir) {
		strcpy(completePath, m_dir);
		if (m_path) {
			strcat(completePath, m_path);
		}
	} else if (m_path) {
		strcpy(completePath, m_path);
	}
}

unsigned int Directory::size() {

	unsigned int size = 0;
	if (m_dir) {
		size += strlen(m_dir);
	}
	if (m_path) {
		size += strlen(m_path);
	}

	return size;
}

bool Directory::isSlashAtEndOfDir() {
	return m_dir[strlen(m_dir) - 1] == '/';
}

unsigned int Directory::changePath(const char* path) {
	if (path == NULL) {
		return 0;
	}

	if (strlen(path) == 0) {
		return 0;
	}

	m_path = new char[strlen(path) + 1];
	strcpy(m_path, path);

	return strlen(m_path);
}
