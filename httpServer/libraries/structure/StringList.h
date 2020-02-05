//
// Created by root on 04-02-20.
//

#ifndef SERVER_STRINGLIST_H
#define SERVER_STRINGLIST_H

#include <string.h>

#include "../Logger.h"

namespace Structure {

    class StringList {
        unsigned int MAX_ITEMS;
        char **m_list;
        unsigned int m_index;

    public:
        StringList(unsigned int max);
        virtual ~StringList();

        int add(const char *value);
        const char* operator[](unsigned int index);
        const int getLength();
    };

}

#endif //SERVER_STRINGLIST_H
