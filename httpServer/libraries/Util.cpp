//
// Created by root on 03-02-20.
//

#include "Util.h"


const char* Util::boolToStr(bool value) {
    return value ? "true" : "false";
}

/*TODO: Change insecure token generator , use a library instead*/
void Util::generateToken(char *token, unsigned int length) {
    static const char alphanumeric[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";

    srand(time(NULL));

    for (unsigned int index = 0; index < length; index++) {
        token[index] = alphanumeric[rand() % (sizeof(alphanumeric) - 1)];
    }

    token[length] = 0;
}

char* Util::clone(const char* stringValue) {
    if (!stringValue) {
        return NULL;
    }

    unsigned int length = strlen(stringValue);
    char* clone = new char[length + 1]();
    strcpy(clone, stringValue);
    clone[length] = 0;

    return clone;
}