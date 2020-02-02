/*
 * PostRequest.h
 *
 *  Created on: Mar 24, 2019
 *      Author: root
 */

#ifndef SRC_LIBRARIES_NETWORK_POSTREQUEST_H_
#define SRC_LIBRARIES_NETWORK_POSTREQUEST_H_

#include "Request.h"
#include "Configuration.h"

namespace Network {

class PostRequest : public Request {

public:
	PostRequest(File* file, Configuration* config);
	virtual ~PostRequest();

	void prepare(char* lines);
	void process();
};

} /* namespace network */

#endif /* SRC_LIBRARIES_NETWORK_POSTREQUEST_H_ */
