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

        for(unsigned int index = 0; index < MAX_URL_PARTS; index++) {
            delete [] m_urlParts[index];
        }
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

    unsigned int Request::getPathPartsLength(const char* urlPath) {
        char* url = Util::clone(urlPath);

        char* part = strtok(url, "/");
        unsigned int count = 0;

        while(part) {
            if (strlen(part)) {
                count++;
            }
            part = strtok(NULL, "/");
        }

        delete url;
        return count;
    }

    void Request::storePathParts(const char* urlPath) {
        char* url = Util::clone(urlPath);

        m_urlParts = new char*[MAX_URL_PARTS];
        unsigned int index = 0;

        char* part = strtok(url, "/");
        while(part) {
            unsigned int lengthPart = strlen(part);
            m_urlParts[index] = new char[lengthPart + 1];
            strcpy(m_urlParts[index], part);
            m_urlParts[index][lengthPart] = 0;

            part = strtok(NULL, "/");
            index++;
        }

        delete [] url;
    }

    void Request::parseParameters(const char* parameters) {

        if (!parameters) {
            return;
        }

        char QUERY[1024];
        strcpy(QUERY, parameters);

        char* pParameter = strtok(QUERY, "&");
        while(pParameter) {

            char PARAM[512];
            strcpy(PARAM, pParameter);
            char* token = strtok(PARAM, "=");
            while(token) {
                Pair* pair = new Pair();
                pair->setKey(token);

                token = strtok(NULL, "=");
                if (token) {
                    pair->setValue(token);
                    m_parameters = pair;
                }
            }

            pParameter = strtok(NULL, "&");
        }
    }

    bool Request::pickParametersFromPath(const char* urlPath) {

        if (!urlPath) {
            Logger::getInstance()->warning("No input url path to parse.");

            return false;
        }

        if ((*pController)[urlPath]) {
            return false;
        }

        MAX_URL_PARTS = getPathPartsLength(urlPath);
        storePathParts(urlPath);
        const char* parametersTape = pController->paramsChecker(m_urlParts, MAX_URL_PARTS);
        parseParameters(parametersTape);

        return m_parameters.getLength();
    }

} /* namespace network */
