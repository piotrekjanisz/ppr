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
    virtual Array<float> getPositions(double frameNum);
private:
    HdfProcessor _hdfProcessor;
    Step* _step;
    std::vector<Step*> _steps;
};

#endif	/* HDFDATAPROVIDER_H */

