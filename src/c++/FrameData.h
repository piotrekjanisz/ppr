/* 
 * File:   FrameData.h
 * Author: piotrek
 *
 * Created on 15 listopad 2010, 20:08
 */

#ifndef FRAMEDATA_H
#define	FRAMEDATA_H

#include "eq/eq.h"
#include "GLFrame.h"
#include "vmmlib/vmmlib.hpp"
#include <cstring>
#include <iostream>

class FrameData : public eq::Object
{
public:
	FrameData();

    virtual ~FrameData();

    void setCameraTransformation(float* matrix)
    {
    	setDirty(DIRTY_ALL_PARAMS);
    	_cameraTransformation.set(&matrix[0], &matrix[16], false);

    }

    void setCameraRotation(float* matrix)
    {
    	setDirty(DIRTY_ALL_PARAMS);
    	_cameraRotation.set(&matrix[0], &matrix[16], false);
    }

    void setModelTransformation(const vmml::mat4f& matrix)
    {
    	setDirty(DIRTY_ALL_PARAMS);
    	_modelTransformation = matrix;
    }

    void setLightDirection(const vmml::vec4f& lightDirection)
    {
    	setDirty(DIRTY_ALL_PARAMS);
    	_lightDirection = lightDirection;
    }

    void setLightPosition(const vmml::vec4f& lightPosition)
    {
    	setDirty(DIRTY_ALL_PARAMS);
    	_lightPosition = lightPosition;
    }

    void setFrameNum(float frameNum)
    {
    	setDirty(DIRTY_ALL_PARAMS);
    	_frameNum = frameNum;
    }

    void incFrameNum(float inc)
    {
    	setDirty(DIRTY_ALL_PARAMS);
    	_frameNum += inc;
    }

    float getFrameNum() const
    {
    	return _frameNum;
    }

    const vmml::mat4f& getCameraTransformation() const
    {
    	return _cameraTransformation;
    }

    vmml::mat4f getCameraRotation() const
    {
    	return _cameraRotation;
    }

    const vmml::mat4f& getModelTransformation() const
    {
    	return _modelTransformation;
    }

    vmml::vec4f getLightDirectionInCameraSpace() const
    {
    	return _cameraRotation * _lightDirection;
    }

    vmml::vec4f getLightPositionInCameraSpace() const
    {
    	return _cameraTransformation * _lightPosition;
    }

    vmml::vec4f getCameraPosition() const
    {
    	return _cameraTransformation.get_column(3);
    }

    vmml::vec4f getCameraUp() const
    {
    	return _cameraTransformation.get_column(1);
    }

protected:
    virtual void serialize(eq::net::DataOStream& os,
                           const uint64_t dirtyBits);

    virtual void deserialize(eq::net::DataIStream& is,
                             const uint64_t dirtyBits);

    enum DirtyBits
    {
    	DIRTY_ALL_PARAMS = eq::Object::DIRTY_CUSTOM << 0
    };

private:
    vmml::mat4f _cameraTransformation;
    vmml::mat4f _cameraRotation;
    vmml::mat4f _modelTransformation;
    vmml::vec4f _lightDirection;
    vmml::vec4f _lightPosition;
    float _frameNum;
};

#endif	/* FRAMEDATA_H */

