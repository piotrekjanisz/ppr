/* 
 * File:   RandomDataProvider.cpp
 * Author: piotrek
 * 
 * Created on 7 grudzień 2010, 16:49
 */

#include "RandomDataProvider.h"
#include "utils.h"

RandomDataProvider::RandomDataProvider(int particleNum, int numComponents, float xmin, float xmax, float ymin, float ymax, float zmin, float zmax)
: _particleNum(particleNum)
{
    _data.size = _particleNum * numComponents;
    _data.array = new float[_data.size];
    for (int i = 0; i < _particleNum; i++) {
        _data.array[i * numComponents + 0] = Utils::randomFloat(xmin, xmax);
        _data.array[i * numComponents + 1] = Utils::randomFloat(ymin, ymax);
        _data.array[i * numComponents + 2] = Utils::randomFloat(zmin, zmax);
        for (int j = 3; j < numComponents; j++) {
            _data.array[i * numComponents + j] = 1.0f;
        }
    }
}

Array<float> RandomDataProvider::getPositions(double frameNum)
{
    return _data;
}

