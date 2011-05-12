/*
 * LocalInitData.cpp
 *
 *  Created on: May 12, 2011
 *      Author: piotrek
 */

#include "LocalInitData.h"
#include <cstring>

LocalInitData::LocalInitData()
	: InitData()
{
	setHdfFile("");
	setSphereNum(100000);
}

LocalInitData::~LocalInitData()
{
}

bool LocalInitData::isArgumentWithValue(char** argv, const char* argName)
{
	return (strcmp(*argv, argName) == 0 && *(argv+1));
}

void LocalInitData::processCommandLine(char** argv)
{
	while (*argv) {
		if (isArgumentWithValue(argv, "-hdfFile")) {
			setHdfFile(*(argv+1));
			argv++;
		} else if (isArgumentWithValue(argv, "-sphereNum")) {
			setSphereNum(atoi(*(argv+1)));
			argv++;
		}

		argv++;
	}
}
