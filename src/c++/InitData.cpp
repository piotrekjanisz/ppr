/* 
 * File:   InitData.cpp
 * Author: piotrek
 * 
 * Created on 28 listopad 2010, 19:10
 */

#include "InitData.h"

InitData::InitData() : _frameDataId(co::base::UUID::ZERO) { }

InitData::~InitData() { }

void InitData::getInstanceData(co::DataOStream& os)
{
    os << _frameDataId << _hdfFile << _sphereNum;
}

void InitData::applyInstanceData(co::DataIStream& is)
{
    is >> _frameDataId;
    is >> _hdfFile;
    is >> _sphereNum;
}
