/*
 * Configuration.cpp
 *
 *  Created on: Mar 16, 2019
 *      Author: ralph
 */

#include "Configuration.h"

namespace Network {

Configuration::Configuration() {
	filename = new Filename("httpd.conf");
	directory = new Directory("./config/");
	assembler = new FileAssembler(directory, filename);
	m_configFile = new File(assembler);
    configMap = new Pair*[MAX];
}

Configuration::Configuration(File* configFile) {
	filename = NULL;
	directory = NULL;
	assembler = NULL;
	m_configFile = configFile;
    configMap = new Pair*[MAX];
}

Configuration::~Configuration() {
	if (filename) {
		delete filename;
	}

	if (directory) {
		delete directory;
	}

	if (assembler) {
		delete assembler;
	}

	if (m_configFile) {
		m_configFile->close();
		delete m_configFile;
	}

    for(unsigned int index = 0; index < MAX; index++) {
	    delete configMap[index];
	}
    delete configMap;
}

bool Configuration::read() {

    bool result = true;
    FILE* reference = m_configFile->open(FileAction::Type::READ);

	if (!reference) {
		Logger::getInstance()->error("Cannot open %s file.", m_configFile->getFileAssembler()->getFilename()->get());
		return false;
	}

    char* ptrFile = new char[128];
    unsigned int size = m_configFile->size();
    unsigned int index = 0;

    //Copy the line by line the contents referenced by FILE*
    while(fgets (ptrFile, size, reference)) {
        //Removing the '\n'
        ptrFile[strlen(ptrFile) - 1] = 0;
        //Getting a pair of tokens
        char* pch = strtok(ptrFile, "=");

        if (!pch) {
            continue;
        }

        configMap[index] = new Pair;
        configMap[index]->setKey(pch);
        pch = strtok(NULL, "=");
        if (!pch) {
            result = false;
            continue;
        }
        configMap[index]->setValue(pch);
        index++;
    }

    configMap[index] = NULL;
    m_configFile->close();
    delete [] ptrFile;

    return result;
}

//Chroot and change user and group to nobody.
//Got this function from Simple HTTPD 1.0.
void Configuration::dropPrivileges() {
    struct passwd *pwd;
    struct group *grp;

    if ((pwd = getpwnam(this->operator[]("USER"))) == 0)
    {
        Logger::getInstance()->error("User [%s] not found in /etc/passwd", this->operator[]("USER"));
    	exit(1);
    }

    if ((grp = getgrnam(this->operator[]("GROUP"))) == 0)
    {
        Logger::getInstance()->error("Group [%s] not found in /etc/group", this->operator[]("GROUP"));
    	exit(1);
    }

    if (chdir(this->operator[]("ROOT")) != 0)
    {
        Logger::getInstance()->error("Using chdir() in [%s] failed, %s", this->operator[]("ROOT"), strerror(errno));
        Logger::getInstance()->info("The dir path must exist ");
    	exit(1);
    }

    if (chroot(this->operator[]("ROOT")) != 0)
    {
        Logger::getInstance()->error("Failed chroot() in [%s] , %s", this->operator[]("ROOT"), strerror(errno));
        Logger::getInstance()->info("The app shoudl run as root.");
    	exit(1);
    }

    if (setgid(grp->gr_gid) != 0)
    {
        Logger::getInstance()->error("Using setgid(...) failed");
    	exit(1);
    }

    if (setuid(pwd->pw_uid) != 0)
    {
        Logger::getInstance()->error("Using setuid(...) failed");
    	exit(1);
    }
}

int Configuration::getPort() {
	return atoi(this->operator[]("PORT"));
}

const char* Configuration::operator[](const char* indexKey)
{
    if (!indexKey || strlen(indexKey) == 0)
    {
        Logger::getInstance()->error("key is null");

        return "";
    }

    Pair** iterator = configMap;
    while(*iterator != NULL) {
        if ((*iterator)->hasKey(indexKey)) {
            return (*iterator)->getValue();
        }
        iterator++;
    }

    return "Unknown";
}

}
