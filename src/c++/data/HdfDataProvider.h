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

class HdfDataProvider : public DataProvider
{
public:
    HdfDataProvider(const char* hdfFilePath);
    ~HdfDataProvider();
    virtual boost::shared_ptr<Step> getStep(double frameNum, double begin, double end, bool additionaData = true);
    virtual int getParticleNum(double frameNum);
private:
    HdfProcessor _hdfProcessor;
    int _stepsNumber;
};

#endif	/* HDFDATAPROVIDER_H */

