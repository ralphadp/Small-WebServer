//
// Created by root on 04-02-20.
//

#include "Rest.h"

namespace Network {

    bool Rest::parseParams(const char* verb) {

        const Template::List<Structure::Url>& urlList = m_urls[verb];
        const Template::List<const char*>& input = m_currentUrl.parts();
        bool onTrack = false;

        unsigned int sizeList = urlList.getLength();
        unsigned int index;
        for (index = 0; index < sizeList; index++) {

            Structure::Url urlItem = urlList[index];
            const Template::List<const char*>& list = urlItem.parts();


            if (input.getLength() != list.getLength()) {
                continue;
            }

            onTrack = false;

            unsigned int size = input.getLength();
            for (unsigned int part = 0; part < size; part++) {
                const char* inputUrlPart = input[part];
                const char* controllerUrlPart = list[part];

                if (strcmp(inputUrlPart, controllerUrlPart) == 0) {
                    onTrack = true;
                } else {
                    if (controllerUrlPart[0] == ':') {
                        onTrack = true;
                        m_parameters[controllerUrlPart] = inputUrlPart;
                    } else {
                        onTrack = false;
                    }
                }
            }

            if (onTrack) {
                break;
            }
        }

        if (!onTrack) {
            m_parameters.clear();
        }

        m_selectedPath = m_urls[verb][index].value();

        return onTrack;
    }

    const char* Rest::process(RequestBag& parameters) {
        m_currentUrl = parameters.getUrlPath();
        bool success = parseParams(parameters.getVerb());
        if (success) {
            parameters.copyRestParams(m_parameters);
        }

        return m_selectedPath.value();
    }

    Template::Map<Structure::String, Structure::String>& Rest::getParameters() {
        return m_parameters;
    }

    void Rest::addGetUrl(const char* path) {
        m_urls["GET"].add(path);
    }

    void Rest::addPostUrl(const char* path) {
        m_urls["POST"].add(path);
    }
}