/*
 * FileSorter.h
 *
 *  Created on: 04-03-2011
 *      Author: darek
 */

#ifndef FILESORTER_H_
#define FILESORTER_H_
#include "HdfProcessor.h"

class FileSorter {
public:
	FileSorter();
	virtual ~FileSorter();
	static void sortFile(const char* fileName);
};

#endif /* FILESORTER_H_ */
