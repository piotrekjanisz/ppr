/* 
 * File:   FrameData.cpp
 * Author: piotrek
 * 
 * Created on 15 listopad 2010, 20:08
 */

#include "FrameData.h"


FrameData::FrameData()
	: _lightDirection(vmml::vector<4, float>(-1.0f, -1.0f, -1.0f, 1.0f)),
	  _modelTransformation(vmml::mat4f::IDENTITY),
	  _lightPosition(vmml::vector<4, float>(200.0f, 200.0f, 200.0f))
{
}

FrameData::~FrameData() { }

void FrameData::serialize(eq::net::DataOStream& os,
        const uint64_t dirtyBits)
{
    eq::Object::serialize(os, dirtyBits);
    if (dirtyBits & DIRTY_ALL_PARAMS) {
        os << _cameraTransformation;
        os << _cameraRotation;
        os << _modelTransformation;
        os << _lightDirection;
        os << _lightPosition;
        os << _frameNum;
        os << _pointSize;
    }
}

void FrameData::deserialize(eq::net::DataIStream& is,
        const uint64_t dirtyBits)
{
    eq::Object::deserialize(is, dirtyBits);
    if (dirtyBits & DIRTY_ALL_PARAMS) {
    	is >> _cameraTransformation;
    	is >> _cameraRotation;
    	is >> _modelTransformation;
    	is >> _lightDirection;
    	is >> _lightPosition;
    	is >> _frameNum;
    	is >> _pointSize;
    }
}


