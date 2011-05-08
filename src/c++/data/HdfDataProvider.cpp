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
}

boost::shared_ptr<Step> HdfDataProvider::getStep(double frameNum, double begin, double end, bool additionaData)
{
	int frameNumInt = floor(frameNum);
	frameNumInt = frameNumInt % _stepsNumber;
	int particleNum = _hdfProcessor.readParticlesNumber(frameNumInt);
	int firstParticle = floor(particleNum * begin);
	int lastParticle = floor(particleNum * end);
	boost::shared_ptr<Step> retVal(_hdfProcessor.readStep(frameNumInt, firstParticle, lastParticle, additionaData));

	return retVal;
}

int HdfDataProvider::getParticleNum(double frameNum)
{
	int stepNumber = floor(fmod(frameNum, _stepsNumber));
	return _hdfProcessor.readParticlesNumber(stepNumber);
}

HdfDataProvider::~HdfDataProvider() { }



