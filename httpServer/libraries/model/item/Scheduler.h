//
// Created by root on 02-02-20.
//

#ifndef SERVER_SCHEDULER_H
#define SERVER_SCHEDULER_H

#include "../../Logger.h"
#include "../Result.h"
#include "../Model.h"

namespace Model {

    namespace Item {

        class Scheduler : Model {

        public:

            static Result getList(const char *params, const char* templateContent);
            static Result getInfo(const char *params, const char* templateContent);
        };
    }

}


#endif //SERVER_SCHEDULER_H
