//
// Created by root on 30-01-20.
//

#ifndef SRC_LIBRARIES_NETWORK_PAIR_H
#define SRC_LIBRARIES_NETWORK_PAIR_H

#include <string.h>

#include "../Logger.h"

namespace Structure {

    class Pair {
        char* m_key;
        char* m_value;

    public:
        Pair();

        virtual ~Pair();

        bool hasKey(const char *key);

        const char *getValue();

        void setKey(const char *key);

        void setValue(const char *value);
    };

}

#endif //SERVER_PAIR_H
