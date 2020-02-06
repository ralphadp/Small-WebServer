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

#include "RequestBag.h"

namespace Network {

    class Request {

    protected:
        RequestBag m_bag;
        char length[100];
        char sent[500]/*TODO: change to dynamically*/;

        char *lines;
        char *postLine;
        const char* headerList;

        char VERB[8];
        File* pfile;
        Configuration* pConfig;
        Controller::ControllerHandler* pController;

        const unsigned int MAX = 12;
        Structure::Pair **headers;
        unsigned int headerIndex;
        char bufferContent[1000];

        bool parsePath(const char *line);
        bool parseHeader(const char *line);

    public:
        Request(File* file, Configuration* config, Controller::ControllerHandler* controller);
        virtual ~Request();

        virtual void prepare(char* lines) = 0;
        virtual void process() = 0;

        const char *operator[](const char *indexKey);

    };

} /* namespace network */

#endif /* SRC_LIBRARIES_NETWORK_REQUEST_H_ */
