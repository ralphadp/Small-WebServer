//
// Created by root on 02-02-20.
//

#ifndef SERVER_CONFIG_H
#define SERVER_CONFIG_H

#include "../../Logger.h"
#include "../Result.h"
#include "../Model.h"

namespace Model {

    namespace Item {

        class Config : Model {

        public:

            static Result init(const char *params, const char *templateContent);
        };
    }
}


#endif //SERVER_CONFIG_H
