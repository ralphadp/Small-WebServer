//
// Created by root on 12-02-20.
//

#ifndef SERVER_URL_H
#define SERVER_URL_H
#include "../Logger.h"
#include "String.h"
#include "template/List.h"
#include "../Util.h"

namespace Structure {

    class Url : public String {
        Template::List<const char*> m_parts;
    public:
        Url();
        Url(const char*);
        Url(const Url&);
        ~Url();
        void split();
        Template::List<const char*>& parts();
        Url& operator=(const Url &object);

    };
}


#endif //SERVER_URL_H
