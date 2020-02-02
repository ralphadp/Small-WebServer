/*
 * FileAssembler.cpp
 *
 *  Created on: Mar 5, 2019
 *      Author: ralph
 */

#include "FileAssembler.h"

FileAssembler::FileAssembler(Directory* dir, Filename* filename) {
	m_directoryUnit = dir;
	m_filenameUnit = filename;
}

FileAssembler::~FileAssembler() {
}

void FileAssembler::setDirectory(Directory* dir) {
	m_directoryUnit = dir;
}

void FileAssembler::setFilename(Filename* filename) {
	m_filenameUnit = filename;
}

Directory* FileAssembler::getDirectory() {
	return m_directoryUnit;
}

Filename* FileAssembler::getFilename() {
	return m_filenameUnit;
}

unsigned int FileAssembler::size() {
	unsigned int count =
			m_directoryUnit->size()
			+ m_filenameUnit->size()
			+ 1;

	if (!m_directoryUnit->isSlashAtEndOfDir()) {
		count++;
	}

	return count;
}

bool FileAssembler::assemble(char* completeFilename) {
	if (!m_filenameUnit) {
		return false;
	}

	m_directoryUnit->get(completeFilename);

	if (!m_directoryUnit->isSlashAtEndOfDir()) {
		strcat(completeFilename, "/");
	}

	strcat(completeFilename, m_filenameUnit->get());
	strcat(completeFilename, "\0");

	return true;
}
