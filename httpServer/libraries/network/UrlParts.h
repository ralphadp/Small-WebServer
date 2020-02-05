//
// Created by root on 04-02-20.
//

#ifndef SERVER_URLPARTS_H
#define SERVER_URLPARTS_H

#include "../Logger.h"
#include "../structure/StringList.h"
#include "../Util.h"

namespace Network {

    class UrlParts {
        unsigned int MAX_URL_PARTS;
        Structure::StringList* m_urlParts;
    public:
        UrlParts();
        virtual ~UrlParts();

        unsigned int getUrlPartsLength(const char *url);
        int storeUrlParts(const char *url);
        unsigned int size();
        const char* operator[](unsigned int index);
    };

}

#endif //SERVER_URLPARTS_H
