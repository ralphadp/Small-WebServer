//
// Created by root on 02-02-20.
//

#ifndef SERVER_SCHEDULER_H
#define SERVER_SCHEDULER_H

#include "../../Logger.h"
#include "../Result.h"
#include "../Model.h"
#include "../../network/RequestBag.h"

namespace Model {

    namespace Item {

        class Scheduler : Model {

        public:

            static Result getList(Network::RequestBag params, const char* templateContent);
            static Result getInfo(Network::RequestBag params, const char* templateContent);
        };
    }

}


#endif //SERVER_SCHEDULER_H
