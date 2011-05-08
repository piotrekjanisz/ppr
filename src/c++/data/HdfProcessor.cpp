/*
 * HdfReader.cpps
 *
 *  Created on: 10-01-2011
 *      Author: Dariusz Galysa
 */

#include "HdfProcessor.h"
#include <boost/make_shared.hpp>
#include <iostream>
#include <cstdio>
#include <map>
#include <vector>
#include <string>

using namespace std;
using namespace H5;

const char* HdfProcessor::STEP_NAME_TEMPLATE = "Step#%d";
const char* HdfProcessor::COORDINATES_DATASET_NAMES[] = { "x", "y", "z" };
const char* CURRENT_PATH = ".";

HdfProcessor::HdfProcessor(const char* fileName, HdfProcessor::Mode mode) {
	unsigned int accesMode = (mode == READ_ONLY) ? H5F_ACC_RDONLY
			: H5F_ACC_RDWR;
	_file = H5File(fileName, accesMode);
	_stepsNumber = _file.getNumObjs();
}

HdfProcessor::~HdfProcessor() {
	_file.close();
}

int HdfProcessor::getStepsNumber() const {
	return _stepsNumber;
}

int HdfProcessor::getPointsNumber(const Group& group) const {
	DataSet dataSet = group.openDataSet(COORDINATES_DATASET_NAMES[Step::X]);
	DataSpace dataSpace = dataSet.getSpace();
	int pointsNumber = dataSpace.getSimpleExtentNpoints();
	dataSet.close();
	return pointsNumber;
}

const DataSpace HdfProcessor::createMemoryDataSpace(int pointsNumber,
		int dimensionNumber) const {
	hsize_t dimensions[] = { pointsNumber * (Step::COORDINATES_NUMBER) };
	DataSpace memorySpace(1, dimensions);

	hsize_t count[] = { pointsNumber };
	hsize_t start[] = { dimensionNumber };
	hsize_t stride[] = { Step::COORDINATES_NUMBER };
	memorySpace.selectHyperslab(H5S_SELECT_SET, count, start, stride);

	return memorySpace;
}

const DataSpace HdfProcessor::createFileDataSpace(int pointsNumber, int offset) const {
	hsize_t dimensions[] = { pointsNumber + offset };
	hsize_t count[] = { pointsNumber };
	hsize_t start[] = { offset };
	hsize_t stride[] = { 1 };

	DataSpace fileSpace(1, dimensions);

	fileSpace.selectHyperslab(H5S_SELECT_SET, count, start, stride);

	return fileSpace;
}

float* HdfProcessor::readDataSet(const Group & group, const char *dataSetName,
		const DataSpace & memorySpace, const DataSpace & fileSpace, float *buffer) const {
	DataSet dataSet = group.openDataSet(dataSetName);
	dataSet.read(buffer, PredType::NATIVE_FLOAT, memorySpace, fileSpace);
	dataSet.close();
	return buffer;
}

float* HdfProcessor::readCoordinatesFromDataSet(const Group& group, int pointsNumber, int dimensionNumber, int offset, float *buffer) const {
	DataSpace memorySpace = createMemoryDataSpace(pointsNumber, dimensionNumber);
	DataSpace fileSpace = createFileDataSpace(pointsNumber, offset);

	return readDataSet(group, COORDINATES_DATASET_NAMES[dimensionNumber], memorySpace, fileSpace, buffer);
}

float* HdfProcessor::readAdditionalDataFromDataSet(const H5::Group& group,
		const char *dataSetName, int pointsNumber, int offset, float* buffer) const {
	hsize_t dimensions[] = { pointsNumber };
	DataSpace memorySpace(1, dimensions);
	DataSpace fileSpace = createFileDataSpace(pointsNumber, offset);

	return readDataSet(group, dataSetName, memorySpace, fileSpace, buffer);
}

const char *HdfProcessor::getStepName(int stepNumber) const {
	char *stepName = new char[STEP_NAME_MAX_LENGTH];
	sprintf(stepName, STEP_NAME_TEMPLATE, stepNumber);
	return stepName;
}

bool isDatasetWithCoordinates(string& datasetName) {
	for (int i = 0; i < Step::DIMENSION_NUMBER; i++) {
		if (datasetName == HdfProcessor::COORDINATES_DATASET_NAMES[i])
			return true;
	}
	return false;
}

herr_t readAdditionalDatasetName(hid_t groupId, const char* dataSetName,
		void* data) {
	map<string, float*>* datasetsMap = (map<string, float*>*) data;
	string name = dataSetName;
	if (!isDatasetWithCoordinates(name))
		(*datasetsMap)[dataSetName] = NULL;
	return 0;
}

map<string, float*> HdfProcessor::readNamesOfAdditionalDatasets(Group& group) const {
	map<string, float*> datasetsMap;
	group.iterateElems(CURRENT_PATH, NULL, readAdditionalDatasetName,
			&datasetsMap);
	return datasetsMap;
}

map<string, float*> HdfProcessor::readAdditionalData(Group & group,
		int pointsNumber, int offset) const {
	map<string, float*> additionalData = readNamesOfAdditionalDatasets(group);

	map<string, float*>::iterator begin = additionalData.begin();
	map<string, float*>::iterator end = additionalData.end();

	while (begin != end) {

		float *data = new float[pointsNumber];
		begin->second = readAdditionalDataFromDataSet(group,
				begin->first.c_str(), pointsNumber, offset, data);
		++begin;
	}

	return additionalData;
}

Step* HdfProcessor::readStep(int stepNumber, bool withAdditionalData) const {
	int particlesNumber = readParticlesNumber(stepNumber);

	return readStep(stepNumber, 0, particlesNumber, withAdditionalData);
}

int HdfProcessor::readParticlesNumber(int stepNumber) const {
	const char* stepName = getStepName(stepNumber);

	Group group = _file.openGroup(stepName);
	int particlesNumber = getPointsNumber(group);

	group.close();
	delete[] stepName;

	return particlesNumber;
}

Step *HdfProcessor::readStep(int stepNumber, int begin, int end,
		bool withAdditionalData) const {
	const char* stepName = getStepName(stepNumber);

	Group group = _file.openGroup(stepName);
	int pointsNumber = end - begin;

	float* coordinates = new float[(Step::COORDINATES_NUMBER) * pointsNumber];

	for (int i = 0; i < Step::DIMENSION_NUMBER; i++) {
		readCoordinatesFromDataSet(group, pointsNumber, i, begin, coordinates);
	}
	for (int i = Step::DIMENSION_NUMBER; i < Step::COORDINATES_NUMBER; i++) {
		for (int j = 0; j < pointsNumber; j++) {
			coordinates[Step::COORDINATES_NUMBER * j + i] = 1.0f;
		}
	}

	Step* result = new Step(stepName, pointsNumber, coordinates);

	if (withAdditionalData) {
		map<string, float*> additionalData = readAdditionalData(group,
				pointsNumber, begin);
		result->setAdditionalData(additionalData);
	}

	group.close();
	delete[] stepName;

	return result;
}

boost::shared_ptr<Step> HdfProcessor::createEmptyStep()
{
	boost::shared_ptr<Step> retVal = boost::make_shared<Step>();

	int stepsNumber = getStepsNumber();
	int biggestStep = 0;
	for (int i = 0; i < stepsNumber; i++) {
		biggestStep = std::max(biggestStep, readParticlesNumber(i));
	}

	float* coordinates = new float[biggestStep * Step::DIMENSION_NUMBER];
	retVal->setCoordinates(coordinates);
	retVal->setParticlesNumber(biggestStep);

	return retVal;
}
