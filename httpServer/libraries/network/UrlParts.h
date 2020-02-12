//
// Created by root on 04-02-20.
//

#ifndef SERVER_URLPARTS_H
#define SERVER_URLPARTS_H

#include "../structure/template/List.h"
#include "../structure/String.h"
#include "../Util.h"

namespace Network {

    /**
     * Wrapper to get url path
     */
    class UrlParts {

        Template::List<Structure::String> m_urlParts;
    public:

        int storeUrlParts(const char *url);
        unsigned int size();
        const char* operator[](unsigned int index);
    };

}

#endif //SERVER_URLPARTS_H
