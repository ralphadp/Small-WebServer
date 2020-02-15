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
            Controller::ControllerHandler* controller
    ) {
        lines = NULL;
        postLine = NULL;
        pfile = file;
        pController = controller;
        headerList = "Host:User-Agent:Accept:Accept-Language:Accept-Encoding:content-type:origin:Content-Length:Connection:Renge:";

        strcpy(bufferContent, "");
    }

    Request::~Request() {
        delete [] lines;
        delete [] postLine;
    }

    bool Request::parsePath(const char *line) {

        if (!line) {
            return false;
        }

        char* headerLine = Util::clone(line);
        char *pToken = strtok(headerLine, " ");

        if (!pToken) {
            return false;
        }

        if (strcmp(pToken, VERB) == 0) {
            m_bag.setVerb(pToken);

            pToken = strtok(NULL, " ");
            m_bag.setUrlPath(pToken);

            pToken = strtok(NULL, " ");
            m_bag.setVersion(pToken);

            delete [] headerLine;
            return true;
        }

        delete [] headerLine;
        return false;
    }

    bool Request::parseHeader(const char *line) {

        if (!line) {
            return false;
        }

        char* headerLine = Util::clone(line);
        char *pToken = strtok(headerLine, " ");

        if (!pToken) {
            return false;
        }

        if (strstr(this->headerList, pToken)) {

            Structure::String key(pToken);
            pToken = strtok(NULL, " ");
            if (pToken) {
                headers[key] = pToken;
            }

            delete [] headerLine;
            return true;
        }

        delete [] headerLine;
        return false;
    }

    const char* Request::responseCode(unsigned int code) {
        switch (code) {
            case 200:
                return "200 OK";
            case 404:
                return "404 Not Found";
            case 206:
                return "206 Partial Content";
            case 301:
                return "301 Moved Permanently";
            case 401:
                return "401 Unauthorized";
            case 403:
                return "403 Forbidden";
            default:
                return "500 Internal Server Error";
        }
    }

} /* namespace network */
