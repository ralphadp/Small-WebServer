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
#include "../Util.h"
#include "../controller/ControllerHandler.h"

#include "RequestBag.h"

#include "../structure/String.h"
#include "../structure/template/Map.h"

namespace Network {

    class Request {

    protected:
        RequestBag m_bag;
        char length[100];
        char sent[512]/*TODO: change to dynamically*/;

        char *lines;
        char *postLine;
        const char* headerList;

        char VERB[8];
        File* pfile;
        Configuration* pConfig;
        Controller::ControllerHandler* pController;

        Template::Map<Structure::String, Structure::String> headers;
        char bufferContent[1000];

        bool parsePath(const char *line);
        bool parseHeader(const char *line);
        const char* responseCode(unsigned int code);

    public:
        Request(File* file, Configuration* config, Controller::ControllerHandler* controller);
        virtual ~Request();

        virtual void prepare(char* lines) = 0;
        virtual void process() = 0;

    };

} /* namespace network */

#endif /* SRC_LIBRARIES_NETWORK_REQUEST_H_ */
