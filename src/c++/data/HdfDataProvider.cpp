/* 
 * File:   HdfDataProvider.cpp
 * Author: piotrek
 * 
 * Created on 1 marzec 2011, 14:26
 */

#include "HdfDataProvider.h"
#include <cmath>
#include <iostream>
#include <boost/shared_ptr.hpp>

using namespace std;

HdfDataProvider::HdfDataProvider(const char* hdfFilePath)
    : _hdfProcessor(hdfFilePath)
{
	_stepsNumber = _hdfProcessor.getStepsNumber();
    _steps.reserve(_stepsNumber);
    cout << "STEP NUM: " << _hdfProcessor.getStepsNumber() << endl;
    for (int i = 0; i < _hdfProcessor.getStepsNumber(); i++) {
        _steps.push_back(_hdfProcessor.readStep(i));
    }
}

Array<float> HdfDataProvider::getPositions(double frameNum)
{
    int stepNumber = floor(fmod(frameNum, _steps.size()));
    return Array<float>(_steps[stepNumber]->getCoordinates(), _steps[stepNumber]->getParticlesNumber());
}

boost::shared_ptr<Step> HdfDataProvider::getStep(double frameNum, double begin, double end, bool additionaData)
{
	int frameNumInt = floor(frameNum);
	frameNumInt = frameNumInt % _stepsNumber;
	int particleNum = _hdfProcessor.readParticlesNumber(frameNumInt);
	return boost::shared_ptr<Step>(_hdfProcessor.readStep(frameNumInt, floor(particleNum * begin), floor(particleNum * end), additionaData));
}

int HdfDataProvider::getParticleNum(double frameNum)
{
	int stepNumber = floor(fmod(frameNum, _steps.size()));
	return _steps[stepNumber]->getParticlesNumber();
}

HdfDataProvider::~HdfDataProvider() { }



