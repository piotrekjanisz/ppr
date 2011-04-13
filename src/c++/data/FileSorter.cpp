/*
 * FileSorter.cpp
 *
 *  Created on: 04-03-2011
 *      Author: darek
 */

#include "FileSorter.h"
#include "StepSorter.h"


FileSorter::FileSorter() {
	// TODO Auto-generated constructor stub

}

FileSorter::~FileSorter() {
	// TODO Auto-generated destructor stub
}

void FileSorter::sortFile(const char* fileName) {
	HdfProcessor file(fileName, HdfProcessor::READ_WRITE);
	StepSorter sorter;
	int stepsNumber = file.getStepsNumber();
	for (int i = 0; i < stepsNumber; i++) {
		Step* step = file.readStep(i);
		sorter.sort(*step);
//		file.updateStep(*step);
	}
}
