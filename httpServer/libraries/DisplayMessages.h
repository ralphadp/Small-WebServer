/*
 * DisplayMessages.h
 *
 *  Created on: Mar 18, 2019
 *      Author: ralph
 */

#ifndef SRC_LIBRARIES_DISPLAYMESSAGES_H_
#define SRC_LIBRARIES_DISPLAYMESSAGES_H_

#include "Global.h"
#include "Logger.h"

namespace Libraries {

class DisplayMessages {
public:
	DisplayMessages();
	virtual ~DisplayMessages();
	static void initialDisplay();
};

} /* namespace Libraries */

#endif /* SRC_LIBRARIES_DISPLAYMESSAGES_H_ */
