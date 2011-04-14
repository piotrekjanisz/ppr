/* 
 * File:   DataProvider.h
 * Author: piotrek
 *
 * Created on 7 grudzień 2010, 16:46
 */

#ifndef DATAPROVIDER_H
#define	DATAPROVIDER_H

#include "Step.h"
#include <boost/shared_ptr.hpp>

template <typename T>
struct Array
{
    T* array;
    int size;

    Array(T* array, int size)
            : array(array), size(size) {}
    Array()
            : array(0), size(0) {}
};

class DataProvider
{
public:
    virtual Array<float> getPositions(double frameNum) = 0;
    virtual boost::shared_ptr<Step> getStep(double frameNum, double begin, double end, bool additionaData = true) = 0;
    virtual int getParticleNum(double frameNum) = 0;
};

#endif	/* DATAPROVIDER_H */

