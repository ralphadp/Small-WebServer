//
// Created by root on 02-02-20.
//

#ifndef SERVER_MODELHANDLER_H
#define SERVER_MODELHANDLER_H

#include <iostream>

#include "../Global.h"
#include "../Logger.h"
#include "../Filename.h"
#include "../Directory.h"
#include "../file.h"
#include "Result.h"
#include "Model.h"
#include "../network/RequestBag.h"

namespace Model {

    class ModelHandler {

        File* m_templateFile;
        const char* m_templateFilename;
        Result (*m_pAction)(Network::RequestBag, const char*);

        const char *fetchTemplate();
    public:
        explicit ModelHandler(Result (*fn)(Network::RequestBag, const char*), const char *templateFilename);
        virtual ~ModelHandler();

        Result process(Network::RequestBag parameters);
    };

}


#endif //SERVER_MODELHANDLER_H
