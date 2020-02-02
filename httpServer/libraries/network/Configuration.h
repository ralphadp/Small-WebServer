/*
 * Configuration.h
 *
 *  Created on: Mar 16, 2019
 *      Author: ralph
 */

#ifndef SRC_LIBRARIES_NETWORK_CONFIGURATION_H_
#define SRC_LIBRARIES_NETWORK_CONFIGURATION_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>

#include "../Logger.h"
#include "../Filename.h"
#include "../Directory.h"
#include "../file.h"
#include "Pair.h"

namespace Network {

class Configuration {

	const unsigned int MAX = 6;

    Pair** configMap;

	File* m_configFile;

	Filename* filename;/*TODO: need to think twice this example of classes*/
	Directory* directory;/*TODO: need to think twice this example of classes*/
	FileAssembler* assembler;/*TODO: need to think twice this example of classes*/

public:
	Configuration();
	explicit Configuration(File* configFile);
	virtual ~Configuration();
	bool read();
	void dropPrivileges();
	int getPort();
    const char* operator[] (const char* indexKey);
};

}

#endif /* SRC_LIBRARIES_NETWORK_CONFIGURATION_H_ */
