//
// Created by root on 03-02-20.
//

#include "Map.h"

namespace Network {

    Map::Map() {
        m_pMmap = new Pair*[MAX_ITEMS];
        index = 0;
    }

    Map::~Map() {
        for(unsigned int index = 0; index < MAX_ITEMS; index++) {
            delete m_pMmap[index];
        }
        delete m_pMmap;
    }

    Map& Map::operator=(Pair* item) {
        m_pMmap[index++] = item;
    }

    const char *Map::operator[](const char *key) {
        if (!key || strlen(key) == 0) {
            Logger::getInstance()->error("key is null");

            return "";
        }

        Pair **iterator = m_pMmap;
        while (*iterator != NULL) {
            if ((*iterator)->hasKey(key)) {
                return (*iterator)->getValue();
            }
            iterator++;
        }

        return "Unknown";
    }
}