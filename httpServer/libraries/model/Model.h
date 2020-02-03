//
// Created by root on 02-02-20.
//

#ifndef SERVER_MODEL_H
#define SERVER_MODEL_H

namespace Model {

    class Model {
        protected:
            static const char *defaultErrorTemplate;
            static const char *defaultInvalidTemplate;

            static bool verifyToken();
    };

}


#endif //SERVER_MODEL_H
