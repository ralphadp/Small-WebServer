/*
 * PostRequest.cpp
 *
 *  Created on: Mar 24, 2019
 *      Author: root
 */

#include "PostRequest.h"

namespace Network {

PostRequest::PostRequest(File* file, Configuration* config) : Request(file, config)  {
	lines = NULL;
	postLine = NULL;
	message = NULL;
	contentMessageLength = 0;
}

PostRequest::~PostRequest() {
	delete [] lines;
	delete [] postLine;
	delete [] message;
}

void PostRequest::prepare(char* message) {

    if (!message) {
        Logger::getInstance()->warning("No message to process.");

        return;
    }

    Logger::getInstance()->info("POST message:\n%s", message);

    postLine = strtok(message, "\n\r");

	while (postLine) {

		Logger::getInstance()->warning("[%d] %s\n\r", (int)strlen(postLine), postLine);

		if (strstr(postLine, "Content-Length:")) {
			contentMessageLength = atoi(strstr(postLine, " "));
		}

		if (contentMessageLength == (int)strlen(postLine)) {
            Logger::getInstance()->error("----------> Last line: %s",postLine);
			this->message = postLine;
			break;
		}

        postLine = strtok(NULL, "\n\r");
	};
}

void PostRequest::process() {

    const char* response = verifyMessage(this->message)?"true":"false";

	//Note.- The header and the payload are sent separately
	sprintf(payload,
			"{\n"
			"\"key\":\"%s\"\n"
			"\"result\":\"%s\"\n"
			"}"
			, "ki90kid-w3eqwq"
			, response);

	sprintf(length, "%ld", (long)strlen(payload));

	Logger::getInstance()->info("payload:%s", this->message);

	//create response header
	strcpy(sent, "HTTP/1.1 200 OK");
	strcat(sent, "\nServer: httpd 0.3.1\n");
	strcat(sent, "Content-Length: ");
	strcat(sent, length);
	strcat(sent, "\nConnection: close\nContent-Type: ");
	strcat(sent, "application/json");
	strcat(sent, ";charset=");
	strcat(sent, (*pConfig)["CHARSET"]);
	strcat(sent, "\n\n");
	printf("%s", sent);
	pfile->write(sent);

	//create response payload
	strcpy(sent, payload);
	Logger::getInstance()->info("%s", sent);

	pfile->write(sent);

	//close the new_fd Copy
	pfile->closeFD();
}

} /* namespace network */
