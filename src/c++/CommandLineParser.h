/*
 * CommandLineParser.h
 *
 *  Created on: 13-04-2011
 *      Author: piotrek
 */

#ifndef COMMANDLINEPARSER_H_
#define COMMANDLINEPARSER_H_

class CommandLineParser
{
public:
	const char* findArg(int argc, char** argv, const char* argName);
};

#endif /* COMMANDLINEPARSER_H_ */
