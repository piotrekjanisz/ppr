/*
 * HdfReader.cpps
 *
 *  Created on: 10-01-2011
 *      Author: Dariusz Galysa
 */

#include "HdfProcessor.h"
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
		int offset) const {
	hsize_t dimensions[] = { pointsNumber * (Step::COORDINATES_NUMBER) };
	DataSpace memorySpace(1, dimensions);

	hsize_t count[] = { pointsNumber };
	hsize_t start[] = { offset };
	hsize_t stride[] = { Step::COORDINATES_NUMBER };
	memorySpace.selectHyperslab(H5S_SELECT_SET, count, start, stride);

	return memorySpace;
}

float* HdfProcessor::readDataSet(const Group & group, const char *dataSetName,
		const DataSpace & memorySpace, float *buffer) const {
	DataSet dataSet = group.openDataSet(dataSetName);
	dataSet.read(buffer, PredType::NATIVE_FLOAT, memorySpace);
	dataSet.close();
	return buffer;
}

float* HdfProcessor::readCoordinatesFromDataSet(const Group& group,
		const char *dataSetName, int pointsNumber, int offset, float *buffer) const {
	DataSpace memorySpace = createMemoryDataSpace(pointsNumber, offset);
	return readDataSet(group, dataSetName, memorySpace, buffer);
}

float* HdfProcessor::readAdditionalDataFromDataSet(const H5::Group& group,
		const char *dataSetName, float* buffer) const {
	return readDataSet(group, dataSetName, DataSpace::ALL, buffer);
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
		int pointsNumber) const {
	map<string, float*> additionalData = readNamesOfAdditionalDatasets(group);

	map<string, float*>::iterator begin = additionalData.begin();
	map<string, float*>::iterator end = additionalData.end();

	while (begin != end) {

		float *data = new float[pointsNumber];
		begin->second = readAdditionalDataFromDataSet(group,
				begin->first.c_str(), data);
		++begin;
	}

	return additionalData;
}

Step* HdfProcessor::readStep(int stepNumber, bool withAdditionalData) const {
	const char* stepName = getStepName(stepNumber);

	Group group = _file.openGroup(stepName);
	int pointsNumber = getPointsNumber(group);

	float* coordinates = new float[(Step::COORDINATES_NUMBER) * pointsNumber];

	for (int i = 0; i < Step::DIMENSION_NUMBER; i++) {
		readCoordinatesFromDataSet(group, COORDINATES_DATASET_NAMES[i],
				pointsNumber, i, coordinates);
	}

	Step* result = new Step(stepName, pointsNumber, coordinates);

	if (withAdditionalData) {
		map<string, float*> additionalData = readAdditionalData(group,
				pointsNumber);
		result->setAdditionalData(additionalData);
	}

	group.close();
	delete[] stepName;

	return result;
}

void HdfProcessor::updateStep(Step& step) {
	Group group = _file.openGroup(step.getName());
	unlinkAllDatasets(group);
	for (int i = 0; i < Step::DIMENSION_NUMBER; i++) {
		writeCoordinatesToDataSet(group, COORDINATES_DATASET_NAMES[i],
				step.getParticlesNumber(), i, step.getCoordinates());
	}

	map<string, float*>::iterator begin = step.getAdditionalData().begin();
	map<string, float*>::iterator end = step.getAdditionalData().end();
	while (begin != end) {
		createDataSet(group, begin->first.c_str(), DataSpace::ALL, begin->second,
				step.getParticlesNumber());
		++begin;
	}

	group.close();
}

herr_t readDatasetName(hid_t groupId, const char* dataSetName, void* data) {
	vector<string>* datasetNames = (vector<string>*) data;
	string name = dataSetName;
	datasetNames->push_back(dataSetName);
	return 0;
}

void HdfProcessor::unlinkAllDatasets(Group& group) {
	vector<string> datasetNames;
	group.iterateElems(CURRENT_PATH, NULL, readDatasetName, &datasetNames);

	vector<string>::iterator beg = datasetNames.begin();
	vector<string>::iterator end = datasetNames.end();
	while (beg != end) {
		group.unlink(*beg);
		++beg;
	}
}

void HdfProcessor::writeCoordinatesToDataSet(Group& group,
		const char *dataSetName, int pointsNumber, int offset,
		const float *buffer) {
	DataSpace memorySpace = createMemoryDataSpace(pointsNumber, offset);
	createDataSet(group, dataSetName, memorySpace, buffer, pointsNumber);
}

void HdfProcessor::createDataSet(Group & group, const char *dataSetName,
		const DataSpace & memorySpace, const float *buffer, int pointsNumber) {
	hsize_t dims[1] = { pointsNumber };
	DataSpace fileSpace(1, dims);

	DataSet dataSet = group.createDataSet(dataSetName, PredType::NATIVE_FLOAT,
			fileSpace);

	dataSet.write(buffer, PredType::NATIVE_FLOAT, memorySpace, DataSpace::ALL);
	dataSet.close();
}

