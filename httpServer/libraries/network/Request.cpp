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
        headerList = "Host:User-Agent:Accept:Accept-Language:Accept-Encoding:content-type:origin:Content-Length:Connection:Renge:";

        headers = new Structure::Pair *[MAX];
        headerIndex = 0;
        strcpy(bufferContent, "");
    }

    Request::~Request() {
        delete [] lines;
        delete [] postLine;

        for (unsigned int index = 0; index < MAX; index++) {
            delete headers[index];
        }
        delete [] headers;
    }

    bool Request::parsePath(const char *line) {

        if (!line) {
            return false;
        }

        char headerLine[strlen(line)];
        strcpy(headerLine, line);

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

            return true;
        }

        return false;
    }

    bool Request::parseHeader(const char *line) {

        if (!line) {
            return false;
        }

        char headerLine[strlen(line)];
        strcpy(headerLine, line);

        char *pToken = strtok(headerLine, " ");

        if (!pToken) {
            return false;
        }

        if (strstr(this->headerList, pToken)) {

            headers[headerIndex] = new Structure::Pair;
            headers[headerIndex]->setKey(pToken);
            pToken = strtok(NULL, " ");

            headers[headerIndex]->setValue(pToken);
            headerIndex++;
            headers[headerIndex] = NULL;

            return true;
        }

        return false;
    }

    const char *Request::operator[](const char *indexKey) {
        if (!indexKey || strlen(indexKey) == 0) {
            Logger::getInstance()->warning("Post header key is null");

            return NULL;
        }

        Structure::Pair **iterator = headers;
        while (*iterator != NULL) {
            if ((*iterator)->hasKey(indexKey)) {
                return (*iterator)->getValue();
            }
            iterator++;
        }

        return NULL;
    }



} /* namespace network */
