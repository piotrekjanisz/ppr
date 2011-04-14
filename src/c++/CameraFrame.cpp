/* 
 * File:   CameraFrame.cpp
 * Author: piotrek
 * 
 * Created on 15 listopad 2010, 21:25
 */

#include "CameraFrame.h"
#include "glus/Glus.h"
#include <iostream>

using namespace std;

CameraFrame::CameraFrame()
: _up(0, 1, 0), _forward(0, 0, -1), _position(0, 0, 0) { }

CameraFrame::CameraFrame(const vmml::vec3d& up, const vmml::vec3d& forward, const vmml::vec3d& position)
: _up(up), _forward(forward), _position(position) { }

CameraFrame::CameraFrame(const CameraFrame& cf)
: _up(cf._up), _forward(cf._forward), _position(cf._position) { }

CameraFrame::~CameraFrame() { }

void CameraFrame::rotateHorizontally(float angle)
{
	_forward = _forward.rotate(angle, vmml::vec3d(0.0f, 1.0f, 0.0f));
	_up = _up.rotate(angle, vmml::vec3d(0.0f, 1.0f, 0.0f));
}

void CameraFrame::rotateVertically(float angle)
{
    vmml::vec3d rotAxis = _up.cross(_forward);
    _forward = _forward.rotate(angle, rotAxis);
    _up = _up.rotate(angle, rotAxis);
    _up.normalize();
    _forward.normalize();
}

void CameraFrame::translateForward(float value)
{
    _position += _forward * value;
}

void CameraFrame::translateX(float value)
{
    _position.x() += value;
}

void CameraFrame::translateZ(float value)
{
    _position.z() += value;
}

vmml::mat4f CameraFrame::getTransform() const
{
    vmml::mat4f retVal;
    vmml::vec3f center = _position + _up;

    Glus::glusLookAtf(retVal.array, _position.x(), _position.y(), _position.z(),
    		center.x(), center.y(), center.z(),
    		_up.x(), _up.y(), _up.z());

    return retVal;
}


