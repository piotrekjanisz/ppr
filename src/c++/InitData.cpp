/* 
 * File:   InitData.cpp
 * Author: piotrek
 * 
 * Created on 28 listopad 2010, 19:10
 */

#include "InitData.h"

InitData::InitData() : _frameDataId(EQ_ID_INVALID) { }

InitData::~InitData() { }

void InitData::getInstanceData(eq::net::DataOStream& os)
{
    os << _frameDataId << _hdfFile << _sphereNum;
}

void InitData::applyInstanceData(eq::net::DataIStream& is)
{
    is >> _frameDataId;
    is >> _hdfFile;
    is >> _sphereNum;
}
