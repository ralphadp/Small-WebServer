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
        pfile = file;
        pConfig = config;
        pController = controller;
        headerList = "Host:User-Agent:Accept:Accept-Language:Accept-Encoding:content-type:origin:Content-Length:Connection:";
    }

    Request::~Request() {
        delete [] lines;
        delete [] postLine;
    }

    /**
     * Does the url has a query part
     * @param path
     * @return
     */
    bool Request::hasQuery(const char* path) {
        return strchr(const_cast<char*>(path), '?') != NULL;
    }

    /**
     * Removes the query from path
     * @param path
     * @return
     */
    char* Request::depreciateQuery(char* path) {
        return strtok(path, "?");
    }

} /* namespace network */
