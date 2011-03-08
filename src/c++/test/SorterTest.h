#ifndef SORTER_TEST_H
#define SORTER_TEST_H

#include "MyTest.h"

class Step;

class SorterTest
{
public:
	SorterTest() {}
	~SorterTest() {}

	void testMedian_1st_dim();

	void testMedian_2nd_dim();

	void testMedian_3rd_dim();

	TEST_SUITE
		TEST(testMedian_1st_dim)
		TEST(testMedian_2nd_dim)
		TEST(testMedian_3rd_dim)
	TEST_SUITE_END

private:

	void printArrayOfVectors(const char* title, float* array, int arraySize, int numOfComponents, int componentsToPrint);

	Step* prepareStep(int particleNum); 
};

#endif
