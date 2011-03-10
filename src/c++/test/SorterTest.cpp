#include "SorterTest.h"
#include "data/StepSorter.h"
#include "data/Step.h"
#include <cstdlib>
#include <iostream>
#include "TestHelper.h"

using namespace std;

void SorterTest::testMedian_1st_dim()
{
	const int PART_NUM = 10;
	const int DIM_NUM = 4;
	const int DIM = 0;

	Step* step = TestHelper::prepareStep(PART_NUM);

	StepSorter sorter;
	sorter.median(step->begin(), step->begin() + (step->end() - step->begin())/2, step->end(), StepSorter::Comparator(DIM)); 	

	float* coordinates = step->getCoordinates();

	for (int i = 0; i < PART_NUM / 2; i++) {
		for (int j = PART_NUM / 2; j < PART_NUM; j++) {
			ASSERT_TRUE(coordinates[i * DIM_NUM + DIM] <= coordinates[j * DIM_NUM + DIM]);
		}
	}
}
	
void SorterTest::testMedian_2nd_dim()
{	
	const int PART_NUM = 10;
	const int DIM_NUM = 4;
	const int DIM = 1;
	Step* step = TestHelper::prepareStep(PART_NUM);

	StepSorter sorter;
	sorter.median(step->begin(), step->begin() + (step->end() - step->begin())/2, step->end(), StepSorter::Comparator(DIM)); 	
	float* coordinates = step->getCoordinates();

	for (int i = 0; i < PART_NUM / 2; i++) {
		for (int j = PART_NUM / 2; j < PART_NUM; j++) {
			ASSERT_TRUE(coordinates[i * DIM_NUM + DIM] <= coordinates[j * DIM_NUM + DIM]);
		}
	}
}

void SorterTest::testMedian_3rd_dim()
{
	const int PART_NUM = 10;
	const int DIM_NUM = 4;
	const int DIM = 2;
	Step* step = TestHelper::prepareStep(PART_NUM);

	StepSorter sorter;
	sorter.median(step->begin(), step->begin() + (step->end() - step->begin())/2, step->end(), StepSorter::Comparator(DIM)); 	
	
	float* coordinates = step->getCoordinates();

	for (int i = 0; i < PART_NUM / 2; i++) {
		for (int j = PART_NUM / 2; j < PART_NUM; j++) {
			ASSERT_TRUE(coordinates[i * DIM_NUM + DIM] <= coordinates[j * DIM_NUM + DIM]);
		}
	}
}
