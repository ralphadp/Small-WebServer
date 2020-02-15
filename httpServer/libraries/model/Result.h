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
        unsigned int m_code;
    public:
        Result();
        Result(const Result& result);
        Result(const char* payload, bool success = true, unsigned int code = 200);
        virtual ~Result();

        inline unsigned int getLength() {
            return m_length;
        }

        inline const char* getPayload() {
            return m_content;
        }

        inline bool isSuccess() {
            return m_success;
        }

        inline unsigned int getCode() {
            return m_code;
        }

        Result& operator=(const Result& result);
    };
}


#endif //SERVER_RESULT_H
