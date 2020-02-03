//
// Created by root on 01-02-20.
//

#ifndef SERVER_USER_H
#define SERVER_USER_H

#include <stdlib.h>
#include <time.h>

#include "../../Logger.h"
#include "../Result.h"
#include "../Model.h"

namespace Model {

    namespace Item {

        class User : Model {

            static bool checkCredentials();
            static void generateToken(char *token, unsigned int length);
        public:
            explicit User();
            virtual ~User();

            static Result login(const char *params, const char* templateContent);
        };
    }

}

#endif //SERVER_USER_H
