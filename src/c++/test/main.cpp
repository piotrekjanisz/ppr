/*
 * main.cpp
 *
 *  Created on: 08-03-2011
 *      Author: piotrek
 */

#include "SorterTest.h"
#include "KdTreeTest.h"

int main(int argc, char** argv)
{
	SorterTest test1;
	test1.suite();

	KdTreeTest test2;
	test2.suite();
	return 0;
}
