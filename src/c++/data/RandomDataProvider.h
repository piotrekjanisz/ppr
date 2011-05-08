/* 
 * File:   RandomDataProvider.h
 * Author: piotrek
 *
 * Created on 7 grudzień 2010, 16:49
 */

#ifndef RANDOMDATAPROVIDER_H
#define	RANDOMDATAPROVIDER_H

#include "DataProvider.h"
#include "Step.h"
#include <boost/shared_ptr.hpp>

class RandomDataProvider : public DataProvider
{
    int _particleNum;
    Array<float> _data;
    boost::shared_ptr<Step> _step;

public:
    RandomDataProvider(int particleNum, int numComponents, float xmin, float xmax, float ymin, float ymax, float zmin, float zmax);
    virtual ~RandomDataProvider() {}

    virtual int getParticleNum(double frameNum);
    virtual boost::shared_ptr<Step> getStep(double frameNum, double begin, double end, bool additionaData = true);
};

#endif	/* RANDOMDATAPROVIDER_H */

