/*
 * Filename.cpp
 *
 *  Created on: Mar 5, 2019
 *      Author: ralph
 */

#include "Filename.h"

/**
 * @param const char* filename set the pointer of the external filename
 */
Filename::Filename(const char* filename) {
	m_filename = filename;
}

Filename::~Filename() {
}

const char* Filename::get() {
	return m_filename;
}

unsigned int Filename::size() {
	return strlen(m_filename);
}

