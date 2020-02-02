/*
 * FileName.h
 *
 *  Created on: Mar 5, 2019
 *      Author: ralph
 */

#ifndef SRC_LIBRARIES_FILENAME_H_
#define SRC_LIBRARIES_FILENAME_H_

#include "string.h"

/**
 * Filename: wrapper class
 */
class Filename {
	const char* m_filename;
public:
	Filename(const char* filename);
	virtual ~Filename();

	const char* get();
	void set(const char* filename);
	unsigned int size();
};

#endif /* SRC_LIBRARIES_FILENAME_H_ */
