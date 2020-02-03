//
// Created by root on 02-02-20.
//

#ifndef SERVER_RESULT_H
#define SERVER_RESULT_H

#include <string.h>

namespace Model {

    class Result {
        unsigned int m_length;
        const char* m_content;
        bool m_success;
    public:
        Result(const char* payload, bool result);
        virtual ~Result();

        unsigned int getLength();
        const char* getPayload();
        const char* getSuccess();
        bool isSuccessful();
    };
}


#endif //SERVER_RESULT_H
