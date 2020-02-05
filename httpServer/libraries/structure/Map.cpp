//
// Created by root on 03-02-20.
//

#include "Map.h"

namespace Structure {

    Map::Map() {
        m_pMmap = new Pair*[MAX_ITEMS];
        m_index = 0;
    }

    Map::~Map() {
        for(unsigned int index = 0; index < MAX_ITEMS; index++) {
            delete m_pMmap[index];
        }
    }

    void Map::add(Pair* item) {
        if (m_index < MAX_ITEMS) {
            m_pMmap[m_index++] = item;
        }
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

    unsigned int Map::getLength() {
        return m_index;
    }
}