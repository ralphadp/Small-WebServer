//
// Created by root on 03-02-20.
//

#ifndef SERVER_MAP_H
#define SERVER_MAP_H

#include "Pair.h"

namespace Structure {

    class Map {

        unsigned int MAX_ITEMS = 6;
        Pair **m_pMmap;
        unsigned int m_index;
    public:
        Map();
        virtual ~Map();

        void add(Pair* item);
        const char *operator[](const char *key);
        bool getLength();
    };
}

#endif //SERVER_MAP_H
