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
        headerList = "Host:User-Agent:Accept:Accept-Language:Accept-Encoding:content-type:origin:Content-Length:Connection:";
    }

    Request::~Request() {
        delete [] lines;
        delete [] postLine;
    }

    bool Request::verifyMessage(char* message) {
        if (strlen(message) < 0) {
            return false;
        }

        //TODO: check message
        return true;
    }

} /* namespace network */
