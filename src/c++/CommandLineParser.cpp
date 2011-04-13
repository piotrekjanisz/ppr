/*
 * CommandLineParser.cpp
 *
 *  Created on: 13-04-2011
 *      Author: piotrek
 */

#include "CommandLineParser.h"
#include <string>
#include <cstring>

using namespace std;

const char* CommandLineParser::findArg(int argc, char** argv, const char* argName)
{
	for (int  i = 0; i < argc; i++) {
		if (strcmp(argv[i], argName) == 0) {
			if (argv[i+1])
				return argv[i+1];
		}
	}

	return 0;
}
