/* 
 * File:   CameraFrame.cpp
 * Author: piotrek
 * 
 * Created on 15 listopad 2010, 21:25
 */

#include "CameraFrame.h"
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
    _forward = _forward.rotate(angle, _up);
    _forward.normalize();
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
    vmml::vec3d cross = _up.cross(_forward);
    vmml::mat4f transform = vmml::mat4f::ZERO;
    vmml::mat4f translation = vmml::mat4f::IDENTITY;

    transform[0][0] = cross.x();
    transform[1][0] = cross.y();
    transform[2][0] = cross.z();

    transform[0][1] = _up.x();
    transform[1][1] = _up.y();
    transform[2][1] = _up.z();

    transform[0][2] = _forward.x();
    transform[1][2] = _forward.y();
    transform[2][2] = _forward.z();

    /*
    transform[0][3] = _position.x();
    transform[1][3] = _position.y();
    transform[2][3] = _position.z();
    */
    transform[3][3] = 1.0f;

    
    translation[0][3] = _position.x();
    translation[1][3] = _position.y();
    translation[2][3] = _position.z();

    //transform *= translation;

    transform *= translation;

    //std::cout << transform << std::endl;

    return transform;
}


