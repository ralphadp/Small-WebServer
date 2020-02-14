//
// Created by root on 04-02-20.
//

#include "Rest.h"

namespace Network {

    const char* Rest::parseParams(const char* verb) {

        const char* restUrl = 0;
        Template::List<Structure::Url>& urlList = m_urls[verb];
        bool onTrack = false;

        for (unsigned int index = 0; index < urlList.getLength(); index++) {

            Structure::Url urlItem = urlList[index];
            const Template::List<const char*>& list = urlItem.parts();
            const Template::List<const char*>& input = m_currentUrl.parts();

            if (input.getLength() != list.getLength()) {
                continue;
            }

            onTrack = false;

            for (unsigned int part = 0; part < input.getLength(); part++) {

                if (strcmp(input[part], list[part]) == 0) {
                    onTrack = true;
                } else {
                    if (list[part][0] == ':') {
                        onTrack = true;
                        restUrl = urlList[index].value();
                        m_parameters[list[part]] = input[part];
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

        return restUrl;
    }

    const char* Rest::process(RequestBag& parameters) {
        m_currentUrl = parameters.getUrlPath();
        const char* restUrl = parseParams(parameters.getVerb());
        if (restUrl) {
            parameters.copyRestParams(m_parameters);
        }

        return restUrl;
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