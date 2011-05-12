/*
 * LocalInitData.h
 *
 *  Created on: May 12, 2011
 *      Author: piotrek
 */

#ifndef LOCALINITDATA_H_
#define LOCALINITDATA_H_

#include "InitData.h"
#include <string>

class LocalInitData : public InitData
{
public:
	LocalInitData();
	virtual ~LocalInitData();

	void processCommandLine(char** argv);

private:
	bool isArgumentWithValue(char** argv, const char* argName);

};

#endif /* LOCALINITDATA_H_ */
