/* 
 * File:   FrameData.cpp
 * Author: piotrek
 * 
 * Created on 15 listopad 2010, 20:08
 */

#include "FrameData.h"

FrameData::~FrameData() { }

void FrameData::serialize(eq::net::DataOStream& os,
        const uint64_t dirtyBits)
{
    eq::Object::serialize(os, dirtyBits);
    if (dirtyBits & DIRTY_CAMERA)
        os << _cameraTransformation;
}

void FrameData::deserialize(eq::net::DataIStream& is,
        const uint64_t dirtyBits)
{
    eq::Object::deserialize(is, dirtyBits);
    if (dirtyBits & DIRTY_CAMERA)
        is >> _cameraTransformation;
}


