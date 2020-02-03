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

namespace Network {

    class Request {

    protected:
        char payload[500] /*TODO: change to dynamically*/;
        char length[100];
        char sent[500]/*TODO: change to dynamically*/;

        char *lines;
        char *postLine;
        char *m_message;
        unsigned int contentMessageLength;
        const char* headerList;

        File* pfile;
        Configuration* pConfig;
        Controller::ControllerHandler* pController;
    public:
        Request(File* file, Configuration* config, Controller::ControllerHandler* controller);
        virtual ~Request();

        virtual void prepare(char* lines) = 0;
        virtual void process() = 0;

    };

} /* namespace network */

#endif /* SRC_LIBRARIES_NETWORK_REQUEST_H_ */
