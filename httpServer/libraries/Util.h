//
// Created by root on 03-02-20.
//

#ifndef SERVER_UTIL_H
#define SERVER_UTIL_H

#include <stdlib.h>
#include <time.h>
#include <string.h>

class Util {
public:
    static const char* boolToStr(bool value);
    static void generateToken(char *token, unsigned int length);
    static char* clone(const char* stringValue);
};


#endif //SERVER_UTIL_H
