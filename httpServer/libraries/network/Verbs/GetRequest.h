/*
 * GetRequest.h
 *
 *  Created on: Mar 24, 2019
 *      Author: root
 */

#ifndef SRC_LIBRARIES_NETWORK_GETREQUEST_H_
#define SRC_LIBRARIES_NETWORK_GETREQUEST_H_

#include "Request.h"
#include "Configuration.h"
#include "../controller/ControllerHandler.h"

namespace Network {

class GetRequest : public Request {
	char code[50];
	char file[200];
	char moved[200];
	char mime[100];

	char *result;
	char *hostname;
	char *hostnamef;
	char *ext;
	char *extf;
	char *rangetmp;
	long range;
public:
	GetRequest(File* file, Configuration* config, Controller::ControllerHandler* controller);
	virtual ~GetRequest();

	void prepare(char* message);
	void process();
};

} /* namespace network */

#endif /* SRC_LIBRARIES_NETWORK_GETREQUEST_H_ */
