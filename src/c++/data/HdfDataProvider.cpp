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
	_stepsNumbers = _hdfProcessor.getStepsNumbers();
}

boost::shared_ptr<Step> HdfDataProvider::getStep(double frameNum, double begin, double end, bool additionaData)
{
	int stepNumInt = getStepNum(frameNum);
	int particleNum = _hdfProcessor.readParticlesNumber(stepNumInt);
	int firstParticle = floor(particleNum * begin);
	int lastParticle = floor(particleNum * end);
	boost::shared_ptr<Step> retVal(_hdfProcessor.readStep(stepNumInt, firstParticle, lastParticle, additionaData));

	return retVal;
}

int HdfDataProvider::getParticleNum(double frameNum)
{
	int stepNumber = getStepNum(frameNum);
	return _hdfProcessor.readParticlesNumber(stepNumber);
}

HdfDataProvider::~HdfDataProvider() { }



