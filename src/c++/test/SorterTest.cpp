#include "SorterTest.h"
#include "data/StepSorter.h"
#include "data/Step.h"
#include <cstdlib>
#include <iostream>

using namespace std;


void SorterTest::printArrayOfVectors(const char* title, float* array, int arraySize, int numOfComponents, int componentsToPrint)
{
	cout << title << endl;
	for (int i = 0; i < arraySize; i++) {
		for (int j = 0; j < componentsToPrint; j++) {
			cout << array[i*numOfComponents + j] << " ";
		}
		cout << endl;
	}
}
	
Step* SorterTest::prepareStep(int particleNum)
{
	Step* step = new Step();
	step->setParticlesNumber(particleNum);
	step->setCoordinates(new float[particleNum*4]);

	for (int i = 0; i < particleNum; i++) {
		for (int j = 0; j < 4; j++) {
			step->getCoordinates()[i*4 + j] = rand() % 100;
		}
	}

	return step;
}

void SorterTest::testMedian_1st_dim()
{
	const int PART_NUM = 10;
	const int DIM_NUM = 4;
	const int DIM = 0;
	Step* step = prepareStep(PART_NUM);

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
	Step* step = prepareStep(PART_NUM);

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
	Step* step = prepareStep(PART_NUM);

	StepSorter sorter;
	sorter.median(step->begin(), step->begin() + (step->end() - step->begin())/2, step->end(), StepSorter::Comparator(DIM)); 	
	
	float* coordinates = step->getCoordinates();

	for (int i = 0; i < PART_NUM / 2; i++) {
		for (int j = PART_NUM / 2; j < PART_NUM; j++) {
			ASSERT_TRUE(coordinates[i * DIM_NUM + DIM] <= coordinates[j * DIM_NUM + DIM]);
		}
	}
}
