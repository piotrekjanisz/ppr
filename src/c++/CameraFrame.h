/* 
 * File:   CameraFrame.h
 * Author: piotrek
 *
 * Created on 15 listopad 2010, 21:25
 */

#ifndef CAMERAFRAME_H
#define	CAMERAFRAME_H

#include "vmmlib/vmmlib.hpp"
#include <iostream>


/**
 * Class for managing camera position and orientation
 */
class CameraFrame
{
public:
    CameraFrame();
    CameraFrame(const vmml::vec3d& up, const vmml::vec3d& forward, const vmml::vec3d& position);
    CameraFrame(const CameraFrame& cf);

    virtual ~CameraFrame();

    void rotateHorizontally(float angle);
    void rotateVertically(float angle);
    void translateForward(float value);
    void translateX(float value);
    void translateZ(float value);

    vmml::mat4f getTransform() const;

private:
    vmml::vec3d _up;
    vmml::vec3d _forward;
    vmml::vec3d _position;
};

#endif	/* CAMERAFRAME_H */

