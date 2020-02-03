//
// Created by root on 01-02-20.
//

#ifndef SERVER_USER_H
#define SERVER_USER_H

#include <stdlib.h>

#include "../../Logger.h"
#include "../Result.h"
#include "../Model.h"
#include "../../Util.h"

namespace Model {

    namespace Item {

        class User : Model {
            static const char* defaultBadCredentialsTemplate;
            static const unsigned int MAX_TOKEN_LENGTH;
            static bool checkCredentials();
        public:

            static Result login(const char *params, const char* templateContent);
        };
    }

}

#endif //SERVER_USER_H
