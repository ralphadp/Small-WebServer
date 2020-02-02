/*
 * Request.cpp
 *
 *  Created on: Mar 24, 2019
 *      Author: root
 */

#include "Request.h"

namespace Network {

Request::Request(File* file, Configuration* config) {
	lines = NULL;
	postLine = NULL;
	message = NULL;
	contentMessageLength = 0;
	pfile = file;
    pConfig = config;
}

Request::~Request() {
	delete [] lines;
	delete [] postLine;
	delete [] message;
}

bool Request::verifyMessage(char* message) {
	if (strlen(message) < 0) {
		 return false;
	}

	//TODO: check message
	return true;
}

} /* namespace network */
