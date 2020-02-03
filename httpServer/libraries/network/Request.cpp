/*
 * Request.cpp
 *
 *  Created on: Mar 24, 2019
 *      Author: root
 */

#include "Request.h"

namespace Network {

    Request::Request(
            File* file,
            Configuration* config,
            Controller::ControllerHandler* controller
    ) {
        lines = NULL;
        postLine = NULL;
        m_message = NULL;
        contentMessageLength = 0;
        pfile = file;
        pConfig = config;
        pController = controller;
        headerList = "Host:User-Agent:Accept:Accept-Language:Accept-Encoding:content-type:origin:Content-Length:Connection:";
    }

    Request::~Request() {
        delete [] lines;
        delete [] postLine;
        delete [] m_message;
    }

} /* namespace network */
