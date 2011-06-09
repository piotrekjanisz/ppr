/* 
 * File:   HdfDataProvider.h
 * Author: piotrek
 *
 * Created on 1 marzec 2011, 14:26
 */

#ifndef HDFDATAPROVIDER_H
#define	HDFDATAPROVIDER_H

#include "DataProvider.h"
#include "HdfProcessor.h"
#include "Step.h"
#include <vector>
#include <cmath>

class HdfDataProvider : public DataProvider
{
public:
    HdfDataProvider(const char* hdfFilePath);
    ~HdfDataProvider();
    virtual boost::shared_ptr<Step> getStep(double frameNum, double begin, double end, bool additionaData = true);
    virtual int getParticleNum(double frameNum);

    int getStepsNumber() const { return _stepsNumbers.size(); }

private:
    HdfProcessor _hdfProcessor;

    std::vector<int> _stepsNumbers;

    int getStepNum(double frame)
    {
    	int frameNumInt = floor(frame);
    	frameNumInt = frameNumInt % getStepsNumber();
    	return _stepsNumbers[frameNumInt];
    }
};

#endif	/* HDFDATAPROVIDER_H */

