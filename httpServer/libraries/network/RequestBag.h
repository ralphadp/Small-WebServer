//
// Created by root on 04-02-20.
//

#ifndef SERVER_REQUESTBAG_H
#define SERVER_REQUESTBAG_H

#include <string.h>

#include "../structure/String.h"
#include "../structure/template/Map.h"

namespace Network {

    class RequestBag {
        char m_verb[8];
        char m_urlPath[256];
        char m_version[16];
        char *m_message;
        unsigned int contentMessageLength;
        Template::Map<Structure::String, Structure::String> m_restParameters;
        Template::Map<Structure::String, Structure::String> m_queryParameters;
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
        Template::Map<Structure::String, Structure::String>& getRestParameters();
        void copyRestParams(const Template::Map<Structure::String, Structure::String>& restParameters);
        /*TODO: Query parameters should be defined and implemented in a inherited class*/
        Template::Map<Structure::String, Structure::String>& getQueryParameters();
        void copyQueryParams(const Template::Map<Structure::String, Structure::String>& restParameters);

        bool hasQuery();
        char* removeQueryFromUrl();
    };
}

#endif //SERVER_REQUESTBAG_H
