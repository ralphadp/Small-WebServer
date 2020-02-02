/*
 * FileAssembler.h
 *
 *  Created on: Mar 5, 2019
 *      Author: ralph
 */

#ifndef SRC_FILEASSEMBLER_H_
#define SRC_FILEASSEMBLER_H_

#include "../libraries/Directory.h"
#include "../libraries/Filename.h"

class FileAssembler {
	Directory* m_directoryUnit;
	Filename* m_filenameUnit;
public:
	FileAssembler(Directory* dir, Filename* filename);
	virtual ~FileAssembler();

	void setDirectory(Directory* dir);
	void setFilename(Filename* filename);
	Directory* getDirectory();
	Filename* getFilename();
	unsigned int size();
	bool assemble(char* completeFilename);
};

#endif /* SRC_FILEASSEMBLER_H_ */
