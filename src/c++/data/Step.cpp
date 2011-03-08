/*
 * Step.cpp
 *
 *  Created on: 10-01-2011
 *      Author: Dariusz Galysa
 */

#include "Step.h"
#include <iostream>
#include <cstring>
#include <map>

const int MAX_PRINTED_POINTS = 8;

using namespace std;

Step::Step() :
	_coordinates(NULL) {
}

Step::Step(string name, int pointsNumber, float *coordinates) :
	_name(name), _particlesNumber(pointsNumber), _coordinates(coordinates) {
}

Step::Step(const Step & other) {
	copyData(other);
}

Step::~Step() {
	deleteData();
}

Step & Step::operator =(const Step & other) {
	deleteData();
	copyData(other);
	return *this;
}

void Step::copyData(const Step& other) {
	this->_name = other._name;
	this->_particlesNumber = other._particlesNumber;

	this->_coordinates = new float[COORDINATES_NUMBER * this->_particlesNumber];
	memcpy(this->_coordinates, other._coordinates, sizeof(float)
			* (this->_particlesNumber));

	map<string, float*>::const_iterator begin = other._additionalData.begin();
	map<string, float*>::const_iterator end = other._additionalData.end();

	while (begin != end) {
		float* array = new float[this->_particlesNumber];
		memcpy(array, begin->second, sizeof(float) * this->_particlesNumber);

		this->_additionalData[begin->first] = array;
		++begin;
	}
}

void Step::deleteData() {
	if (_coordinates != NULL)
		delete[] _coordinates;

	map<string, float*>::iterator begin = _additionalData.begin();
	map<string, float*>::iterator end = _additionalData.end();
	while (begin != end) {
		if (begin->second != NULL)
			delete[] begin->second;
		++begin;
	}
	_additionalData.clear();
	_particlesNumber = 0;
}

float *Step::getCoordinates() const {
	return _coordinates;
}

string Step::getName() const {
	return _name;
}

int Step::getParticlesNumber() const {
	return _particlesNumber;
}

void Step::setCoordinates(float *coordinates) {
	_coordinates = coordinates;
}

void Step::setName(string name) {
	_name = name;
}

void Step::setParticlesNumber(int particlesNumber) {
	_particlesNumber = particlesNumber;
}

void Step::setAdditionalData(std::map<std::string, float*> additionalData) {
	_additionalData = additionalData;
}

void printArray(ostream & stream, float *array, int pointsNumber) {
	//int printedPointsNumber = pointsNumber < MAX_PRINTED_POINTS ? pointsNumber
	//		: MAX_PRINTED_POINTS;

	stream << "{ " << endl;

	/*for (int i = 0; i < printedPointsNumber; i++) {
		stream << array[i] << " ";
	}

	if (printedPointsNumber < pointsNumber)
		stream << "... ";*/
	for (int i = 0; i < pointsNumber / 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << array[4*i +j] << " ";
		}
		cout << endl;
	}

	stream << "}" << endl;
}

ostream& operator<<(ostream & stream, const Step & step) {
	stream << "Step name: " << step._name << ", points number: "
			<< step._particlesNumber << endl;

	stream << "Coordinates: ";
	printArray(stream, step._coordinates, step._particlesNumber
			* (Step::COORDINATES_NUMBER));

	stream << "Additional data: " << endl;

	map<string, float*>::const_iterator begin = step._additionalData.begin();
	map<string, float*>::const_iterator end = step._additionalData.end();
	while (begin != end) {
		cout << "\t" << begin->first << ": ";
		printArray(stream, begin->second, step._particlesNumber);
		++begin;
	}

	return stream;
}

int Step::getNumberOfAdditionalParams() const {
	return _additionalData.size();
}

Step::Iterator Step::begin() {
	return Step::Iterator(this, 0);
}

Step::Iterator Step::end() {
	return Step::Iterator(this, this->_particlesNumber);
}

Step::Iterator Step::at(int n) {
	return Step::Iterator(this, n);
}

void iter_swap(Step::Iterator& it1, Step::Iterator& it2) {
	float* tmp = new float[Step::COORDINATES_NUMBER];

	float* coordinates1 = it1.step->_coordinates + it1.index
			* Step::COORDINATES_NUMBER;
	float* coordinates2 = it2.step->_coordinates + it2.index
			* Step::COORDINATES_NUMBER;

	memcpy(tmp, coordinates1, Step::COORDINATES_NUMBER * sizeof(float));
	memcpy(coordinates1, coordinates2, Step::COORDINATES_NUMBER * sizeof(float));
	memcpy(coordinates2, tmp, Step::COORDINATES_NUMBER * sizeof(float));

	map<string, float*>::iterator paramsIter1 =
			it1.step->_additionalData.begin();
	map<string, float*>::iterator paramsIter2 =
			it2.step->_additionalData.begin();

	for (int i = 0; i < it1.step->getNumberOfAdditionalParams(); i++) {
		float* params1 = paramsIter1->second;
		float* params2 = paramsIter2->second;
		tmp[0] = params1[it1.index];
		params1[it1.index] = params2[it2.index];
		params2[it2.index] = tmp[0];

		++paramsIter1;
		++paramsIter2;
	}

	delete[] tmp;
}
