//
// Created by root on 04-02-20.
//

#ifndef SERVER_REQUESTBAG_H
#define SERVER_REQUESTBAG_H

#include <string.h>

#include "Map.h"

namespace Network {

    class RequestBag {

    public:
        char m_urlPath[256];
        char m_version[16];
        char *m_message;
        unsigned int contentMessageLength;
        Network::Map m_restParameters;

        RequestBag();
        ~RequestBag();

        const char* getContents();
        const char* getUrlPath();
        const char* getVersion();
        void setContents(const char *content);
        void copyRestParams(const Network::Map&  restParameters);

    };
}


#endif //SERVER_REQUESTBAG_H
