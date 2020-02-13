//
// Created by root on 02-02-20.
//

#ifndef SERVER_RESULT_H
#define SERVER_RESULT_H

#include <string.h>

#include "../Util.h"

namespace Model {

    class Result {
        unsigned int m_length;
        char* m_content;
        bool m_success;
    public:
        Result();
        Result(const Result& result);
        Result(const char* payload, bool success);
        virtual ~Result();

        unsigned int getLength();
        const char* getPayload();
        bool isSuccess();
        Result& operator=(const Result& result);
    };
}


#endif //SERVER_RESULT_H
