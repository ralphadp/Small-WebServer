//
// Created by root on 12-02-20.
//

#ifndef SERVER_URL_H
#define SERVER_URL_H

#include "String.h"
#include "template/List.h"
#include "../Util.h"

namespace Structure {

    class Url : public String {
        Template::List<Structure::String> m_parts;
    public:
        Url();
        Url(const char*);
        Url(const String&);
        void split();
        const Template::List<Structure::String>& parts();

    };
}


#endif //SERVER_URL_H
