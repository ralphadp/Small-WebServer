/*
 * PostRequest.h
 *
 *  Created on: Mar 24, 2019
 *      Author: root
 */

#ifndef SRC_LIBRARIES_NETWORK_POSTREQUEST_H_
#define SRC_LIBRARIES_NETWORK_POSTREQUEST_H_

#include "Request.h"
#include "Configuration.h"
#include "../controller/ControllerHandler.h"
#include "Pair.h"

namespace Network {

    class PostRequest : public Request {
        char m_urlPath[256];
        char m_version[16];
        const unsigned int MAX = 12;
        Pair** headers;
        unsigned int headerIndex;
        char bufferContent[1000];
    public:
        PostRequest(File* file, Configuration* config, Controller::ControllerHandler* controller);
        virtual ~PostRequest();

        void prepare(char* lines);
        void process();

        const char* operator[](const char* indexKey);

    private:
        void setContents(const char* content);
        bool parsePath(const char* line);
        bool parseHeader(const char* line);
        bool parseContent(const char* line);
    };

} /* namespace network */

#endif /* SRC_LIBRARIES_NETWORK_POSTREQUEST_H_ */
