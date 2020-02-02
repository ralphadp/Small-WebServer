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

namespace Network {

    class Request {

    protected:
        char payload[500] /*TODO: change to dynamically*/;
        char length[100];
        char sent[500]/*TODO: change to dynamically*/;
        char charset[200];

        char *lines;
        char *postLine;
        char *message;
        int contentMessageLength;
        const char* headerList;

        File* pfile;
        Configuration* pConfig;
    public:
        Request(File* file, Configuration* config);
        virtual ~Request();

        virtual void prepare(char* lines) = 0;
        virtual void process() = 0;
    protected:
        bool verifyMessage(char* message);
    };

} /* namespace network */

#endif /* SRC_LIBRARIES_NETWORK_REQUEST_H_ */
