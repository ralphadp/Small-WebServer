//
// Created by root on 04-02-20.
//

#ifndef SERVER_REQUESTBAG_H
#define SERVER_REQUESTBAG_H

#include <string.h>

namespace Network {

    class RequestBag {
    public:
        char m_urlPath[256];
        char m_version[16];
        char *m_message;
        unsigned int contentMessageLength;

        RequestBag();
        ~RequestBag();

        const char* getContents();
        const char* getUrlPath();
        const char* getVersion();
        void setContents(const char *content);

        //friend class Request;
    };
}


#endif //SERVER_REQUESTBAG_H
