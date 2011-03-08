/*
 * HdfReader.h
 *
 *  Created on: 10-01-2011
 *      Author: Dariusz Galysa
 */

#ifndef HDFPROCESSOR_H_
#define HDFPROCESSOR_H_

#include "H5Cpp.h"
#include "Step.h"

class HdfProcessor {
private:
	static const int STEP_NAME_MAX_LENGTH = 64;

	H5::H5File _file;
	int _stepsNumber;

	int getPointsNumber(const H5::Group& group) const;
	float* readDataSet(const H5::Group & group, const char *dataSetName,
			const H5::DataSpace & memorySpace, float *buffer) const;
	void createDataSet(H5::Group & group, const char *dataSetName,
			const H5::DataSpace & memorySpace, const float *buffer, int pointsNumber);

	float* readCoordinatesFromDataSet(const H5::Group& group,
			const char *dataSetName, int pointsNumber, int offset,
			float *buffer) const;
	void writeCoordinatesToDataSet(H5::Group& group, const char *dataSetName,
			int pointsNumber, int offset, const float *buffer);

	float* readAdditionalDataFromDataSet(const H5::Group& group,
			const char *dataSetName, float* buffer) const;

	const char *getStepName(int stepNumber) const;
	const H5::DataSpace
			createMemoryDataSpace(int pointsNumber, int offset) const;
	std::map<std::string, float*> readNamesOfAdditionalDatasets(
			H5::Group& group) const;
	std::map<std::string, float*> readAdditionalData(H5::Group & group,
			int pointsNumber) const;
	void unlinkAllDatasets(H5::Group& group);

public:

	enum Mode { READ_ONLY, READ_WRITE };

	static const char* STEP_NAME_TEMPLATE;
	static const char* COORDINATES_DATASET_NAMES[];

	HdfProcessor(const char* fileName, Mode mode = READ_ONLY);
	virtual ~HdfProcessor();
	int getStepsNumber() const;
	Step* readStep(int stepNumber, bool withAdditionalData = true) const;
	void updateStep(Step& step);
};

#endif /* HDFPROCESSOR_H_ */
