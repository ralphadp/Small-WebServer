//
// Created by root on 03-02-20.
//

#ifndef SERVER_MAP_H
#define SERVER_MAP_H

#include "Pair.h"

namespace Network {

    class Map {

        const unsigned int MAX_ITEMS = 6;
        Pair **m_pMmap;
        unsigned int index;
    public:
        Map();
        virtual ~Map();

        Map& operator=(Pair* item);
        const char *operator[](const char *key);
    };
}

#endif //SERVER_MAP_H
