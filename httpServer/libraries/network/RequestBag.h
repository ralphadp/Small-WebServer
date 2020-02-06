//
// Created by root on 04-02-20.
//

#ifndef SERVER_REQUESTBAG_H
#define SERVER_REQUESTBAG_H

#include <string.h>


#include "../structure/Map.h"

namespace Network {

    class RequestBag {
        char m_verb[8];
        char m_urlPath[256];
        char m_version[16];
        char *m_message;
        unsigned int contentMessageLength;
        Structure::Map m_restParameters;
        Structure::Map m_queryParameters;
    public:

        RequestBag();
        ~RequestBag();

        void setVerb(const char* verb);
        void setUrlPath(const char* url);
        void setVersion(const char* version);
        void setMessageLength(unsigned int length);
        bool setContents(const char *content);
        const char* getVerb() const;
        const char* getContents() const;
        unsigned int getContentLength() const;
        const char* getUrlPath() const;
        const char* getVersion() const;
        Structure::Map& getRestParameters();
        void copyRestParams(const Structure::Map& restParameters);
        /*TODO: Query parameters should be defined and implemented in a inherited class*/
        Structure::Map& getQueryParameters();
        void copyQueryParams(const Structure::Map& restParameters);

        bool hasQuery();
        char* removeQueryFromUrl();
    };
}

#endif //SERVER_REQUESTBAG_H
