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

        public:
            static bool verifyToken(const char* parameters);
            static const char* getErrorTemplate();
            static const char* getInvalidTokenTemplate();
    };

}


#endif //SERVER_MODEL_H
