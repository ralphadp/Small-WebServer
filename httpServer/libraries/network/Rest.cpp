//
// Created by root on 04-02-20.
//

#include "Rest.h"

namespace Network {

    const char* Rest::parseParams(const char* verb) {

        const char* restUrl = 0;
        Template::List<Structure::Url>& urlList = urls[verb];
        bool onTrack = false;

        for (unsigned int index = 0; index < urlList.getLength(); index++) {

            const Template::List<Structure::String>& list = urlList[index].parts();
            const Template::List<Structure::String>& input = m_currentUrl.parts();

            if (input.getLength() != list.getLength()) {
                continue;
            }

            onTrack = false;

            for (unsigned int part = 0; part < input.getLength(); part++) {

                if (input[part] == list[part]) {
                    onTrack = true;
                } else {
                    if (list[part].value()[0] == ':') {
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
        urls["GET"].add(path);
    }

    void Rest::addPostUrl(const char* path) {
        urls["POST"].add(path);
    }
}