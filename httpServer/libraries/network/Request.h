/*
 * Request.h
 *
 *  Created on: Mar 24, 2019
 *      Author: root
 */

#ifndef SRC_LIBRARIES_NETWORK_REQUEST_H_
#define SRC_LIBRARIES_NETWORK_REQUEST_H_

#include <stdlib.h>

#include "../file.h"
#include "../Logger.h"
#include "Configuration.h"
#include "../controller/ControllerHandler.h"
#include "Map.h"
#include "RequestBag.h"

namespace Network {

    class Request {

        unsigned int MAX_URL_PARTS;
        char** m_urlParts;

        unsigned int getPathPartsLength(const char* url);
        void storePathParts(const char* url);
    protected:
        RequestBag m_bag;
        char length[100];
        char sent[500]/*TODO: change to dynamically*/;

        char *lines;
        char *postLine;
        const char* headerList;

        File* pfile;
        Configuration* pConfig;
        Controller::ControllerHandler* pController;
        Map m_parameters;

    public:
        Request(File* file, Configuration* config, Controller::ControllerHandler* controller);
        virtual ~Request();

        virtual void prepare(char* lines) = 0;
        virtual void process() = 0;

        bool hasQuery(const char* path);
        char* depreciateQuery(char* path);
        void parseParameters(const char* parameters);
        bool pickParametersFromPath(const char *urlPath);
    };

} /* namespace network */

#endif /* SRC_LIBRARIES_NETWORK_REQUEST_H_ */
