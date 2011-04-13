/* 
 * File:   Channel.h
 * Author: piotrek
 *
 * Created on 4 listopad 2010, 20:22
 */

#ifndef CHANNEL_H
#define	CHANNEL_H

#include <eq/eq.h>
#include "glus/Glus.h"
#include "CameraFrame.h"
#include "ShaderProgram.h"
#include "FrameData.h"
#include "data/DataProvider.h"
#include "ppr.h"


class Channel : public eq::Channel
{
public:
    Channel(eq::Window* parent);

    virtual ~Channel();

private:
    const int OBJ_NUM;;
    const int SPHERE_NUM_SLICES;

    GLfloat _modelMatrix[16];
    GLfloat _modelViewMatrix[16];

    mutable ppr::Matrix4f _projectionMatrix;

    int _pointsBufferId;
    int _vertexLocation;
    int _lightDirectionLocation;
    int _lightPositionLocation;
    int _cameraRotationLocation;
    int _projectionMatrixLocation;
    int _modelViewMatrixLocation;
    int _cameraPositionLocation;
    int _cameraUpLocation;
    int _vao;
    int _instanceDataUBO;

    ShaderProgram _shaderProgram;

    DataProvider* _dataProvider;
    int _indicesNumber;

    float _eyeX;
    float _eyeY;
    float _eyeZ;
    float _xRotation;
    float _yRotation;
    float _zTranslation;

    int _frameCount;
    double _prevTime;
    double _time;
    double _measureTime;
    eq::base::Clock _clock;

    double _frameNum;
protected:
    void frameDraw(const uint32_t spin);
    void applyFrustum() const;

    const FrameData& getFrameData() const;
};

#endif	/* CHANNEL_H */

