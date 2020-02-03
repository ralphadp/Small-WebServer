//
// Created by root on 02-02-20.
//

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include "../../Logger.h"
#include "../Result.h"
#include "../Model.h"

namespace Model {

    namespace Item {

        class Server : Model {

            static bool verifyToken();

        public:
            explicit Server();
            virtual ~Server();

            static Result notFound(const char *params, const char *templateContent);
        };
    }
}

#endif //SERVER_SERVER_H
