/*
 * file.h
 *
 *  Created on: Jan 02, 2019
 *      Author: ralph
 */

#ifndef LIBRARIES_FILE_H
#define LIBRARIES_FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h> /*directory entity*/
#include <unistd.h>
#include <errno.h>

#include "../libraries/Logger.h"
#include "../libraries/FileAction.h"
#include "../libraries/Directory.h"
#include "../libraries/Filename.h"
#include "../libraries/FileAssembler.h"

/**
 * File handler class
 */
class File
{
	int m_file_descriptor_reference;
	FILE *m_file_reference;
	FileAssembler* m_assembler;

	int buffer_counter;
	char* buffer;
	int buffer_chunks;

	char start[100];
	char end[100];
    char contentLength[100];

	const long SIZE = 1048576;

	long int readBytesCount;

public:
	File(FileAssembler* assembler);
	~File();

	void setFileAssembler(FileAssembler* assembler);
	void setFileDescriptor(int fileDescriptor);
	FILE* open(FileAction type);
    FILE* open(const char* completeFilename, FileAction type);
	long size();
	char* getStart();
	char* getEnd();
	FileAssembler* getFileAssembler();
    void prepareChunkReading(long range);
    unsigned int write(char* input_data);
    unsigned int writeBuffer();
	unsigned int read_chunk();
    unsigned int read(unsigned int size);
	bool read(char* output_data, unsigned int size_data);
	void readWriteChunk();
	unsigned int readContents(char* output_data);
	char* getBuffer();
    const char* GetContentLength();
	void close();
	void closeFD();

};

#endif /* LIBRARIES__FILE_H */
