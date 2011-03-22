/* 
 * File:   HdfDataProvider.cpp
 * Author: piotrek
 * 
 * Created on 1 marzec 2011, 14:26
 */

#include "HdfDataProvider.h"
#include <cmath>
#include <iostream>

using namespace std;

HdfDataProvider::HdfDataProvider(const char* hdfFilePath)
    : _hdfProcessor(hdfFilePath)
{
    _steps.reserve(_hdfProcessor.getStepsNumber());
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

int HdfDataProvider::getParticleNum(double frameNum)
{
	int stepNumber = floor(fmod(frameNum, _steps.size()));
	return _steps[stepNumber]->getParticlesNumber();
}

HdfDataProvider::~HdfDataProvider() { }



