/*
 * FileAction.cpp
 *
 *  Created on: Mar 9, 2019
 *      Author: ralph
 */

#include "FileAction.h"

FileAction::FileAction(Type type) {
	m_type = type;
}

const char* FileAction::get() {
	return types[m_type];
}

