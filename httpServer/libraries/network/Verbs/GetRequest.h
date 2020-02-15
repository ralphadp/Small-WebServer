/*
 * GetRequest.h
 *
 *  Created on: Mar 24, 2019
 *      Author: root
 */

#ifndef SRC_LIBRARIES_NETWORK_GETREQUEST_H_
#define SRC_LIBRARIES_NETWORK_GETREQUEST_H_

#include "../Request.h"
#include "../Configuration.h"
#include "../../controller/ControllerHandler.h"
#include "../../structure/String.h"
#include "../../structure/template/Map.h"
#include "../../Util.h"

namespace Network {

    namespace Verbs {

        class GetRequest : public Request {
            unsigned int code;
            char file[200];
            char moved[256];
            char mime[128];

            char *resultPath;

            char *hostnamef;
            char *ext;
            char *extf;
            char *rangetmp;
            long range;

            Template::Map<Structure::String, Structure::String> m_query;
        public:
            GetRequest(File *file, Controller::ControllerHandler *controller);

            virtual ~GetRequest();

            void prepare(char *message);

            void process();

            bool parseQuery(const char* path);

            void setNotFound();
        };

    } /* namespace Verbs */

} /* namespace network */

#endif /* SRC_LIBRARIES_NETWORK_GETREQUEST_H_ */
