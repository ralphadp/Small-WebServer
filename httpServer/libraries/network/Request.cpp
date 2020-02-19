/*
 * Request.cpp
 *
 *  Created on: Mar 24, 2019
 *      Author: root
 */

#include "Request.h"

namespace Network {

    Request::Request(
            File* file,
            Controller::ControllerHandler* controller
    ) {
        lines = NULL;
        postLine = NULL;
        pfile = file;
        pController = controller;
        headerList = "Host:User-Agent:Accept:Accept-Language:Accept-Encoding:content-type:origin:Content-Length:Connection:Renge:";
        code = 500;
        strcpy(bufferContent, "");
        charset = Network::Configuration::get()->config("CHARSET");
        strcpy(movedHeaderResponse, "");
    }

    Request::~Request() {
        delete [] lines;
        delete [] postLine;
    }

    bool Request::parsePath(const char *line) {

        if (!line) {
            return false;
        }

        char* headerLine = Util::clone(line);
        char *pToken = strtok(headerLine, " ");

        if (!pToken) {
            return false;
        }

        if (strcmp(pToken, VERB) == 0) {
            m_bag.setVerb(pToken);

            pToken = strtok(NULL, " ");
            m_bag.setUrlPath(pToken);

            pToken = strtok(NULL, " ");
            m_bag.setVersion(pToken);

            delete [] headerLine;
            return true;
        }

        delete [] headerLine;
        return false;
    }

    bool Request::parseHeader(const char *line) {

        if (!line) {
            return false;
        }

        char* headerLine = Util::clone(line);
        char *pToken = strtok(headerLine, " ");

        if (!pToken) {
            return false;
        }

        if (strstr(this->headerList, pToken)) {

            Structure::String key(pToken);
            pToken = strtok(NULL, " ");
            if (pToken) {
                headers[key] = pToken;
            }

            delete [] headerLine;
            return true;
        }

        delete [] headerLine;
        return false;
    }

    const char* Request::responseCode(unsigned int code) {
        switch (code) {
            case 200:
                return "200 OK";
            case 404:
                return "404 Not Found";
            case 206:
                return "206 Partial Content";
            case 301:
                return "301 Moved Permanently";
            case 401:
                return "401 Unauthorized";
            case 403:
                return "403 Forbidden";
            default:
                return "500 Internal Server Error";
        }
    }

    const char* Request::getMime(const char* file) {

        if (!file || strlen(file) == 0) {
            return "";
        }

        char* ext = NULL;
        char* extension = strchr(const_cast<char*>(file), '.');

        if (!extension) {
            return "text/plain";
        }

        do {
            ext = ++extension;
            extension = strchr(extension, '.');
        } while(extension);


        if (strcmp(ext, "json") == 0) {
            return "application/json";
        } else if (strcmp(ext, "html") == 0) {
            return "text/html";
        } else if (strcmp(ext, "jpg") == 0) {
            charset = NULL;
            return "image/jpeg";
        } else if (strcmp(ext, "gif") == 0) {
            charset = NULL;
            return "image/gif";
        } else if (strcmp(ext, "png") == 0) {
            charset = NULL;
            return "image/png";
        } else if (strcmp(ext, "css") == 0) {
            return "text/css";
        }

        return "application/octet-stream";
    }

    void Request::createResponseHeader(const char* length, const char* file) {
        //create response header
        strcpy(sent, "HTTP/1.1 ");
        strcat(sent, responseCode(code));
        strcat(sent, "\nServer: httpd ");
        strcat(sent, Global::VERSION);

        if (code == 301) {
            strcat(sent, movedHeaderResponse);
        }

        strcat(sent, "\nContent-Length: ");
        strcat(sent, length);

        if (code == 206) {
            strcat(sent, "\nContent-Range: bytes ");
            strcat(sent, pfile->getStart());
            strcat(sent, "-");
            strcat(sent, pfile->getEnd());
            strcat(sent, "/");
            strcat(sent, pfile->getEnd());
        }

        strcat(sent, "\nConnection: close");

        if (code != 301) {
            strcat(sent, "\nContent-Type: ");
            strcat(sent, getMime(file));
            if (charset) {
                strcat(sent, ";charset=");
                strcat(sent, charset);
            }
        }

        strcat(sent, "\n\n");
    }

} /* namespace network */
