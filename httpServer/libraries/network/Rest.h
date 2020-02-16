//
// Created by root on 04-02-20.
//

#ifndef SERVER_REST_H
#define SERVER_REST_H

#include <string.h>

#include "../Logger.h"
#include "../network/RequestBag.h"
#include "../structure/Url.h"
#include "../structure/template/Map.h"

namespace Network {

    class Rest {
        Structure::String m_selectedPath;
        Structure::Url m_currentUrl;
        Template::Map<Structure::String, Structure::String> m_parameters;
        Template::Map<Structure::String, Template::List<Structure::Url>> m_urls;

    public:
        const char* process(RequestBag& parameters);
        Template::Map<Structure::String, Structure::String>& getParameters();

        void addGetUrl(const char* path);
        void addPostUrl(const char* path);

        bool parseParams(const char* verb);
    };
}

#endif //SERVER_REST_H
