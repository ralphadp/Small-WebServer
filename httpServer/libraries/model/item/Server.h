//
// Created by root on 02-02-20.
//

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include "../../Logger.h"
#include "../Result.h"
#include "../Model.h"
#include "../../network/RequestBag.h"

namespace Model {

    namespace Item {

        class Server : Model {

        public:

            static Result notFound(Network::RequestBag params, const char *templateContent);
        };
    }
}

#endif //SERVER_SERVER_H
