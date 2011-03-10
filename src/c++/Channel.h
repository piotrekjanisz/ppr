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


class Channel : public eq::Channel
{
public:
    Channel(eq::Window* parent);

    virtual ~Channel();

private:
    const int BATCH_NUM;
    const int BATCH_SIZE;
    const int OBJ_NUM;;
    const int SPHERE_NUM_SLICES;

    GLfloat _modelMatrix[16];
    GLfloat _projectionMatrix[16];
    GLfloat _modelViewMatrix[16];

    int _vertexLocation;
    int _normalLocation;
    int _colorLocation;
    int _projectionMatrixLocation;
    int _modelViewMatrixLocation;
    int _instancesCoordsLocation;
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

    CameraFrame _cameraFrame;

    double _frameNum;
protected:
    void frameDraw(const uint32_t spin);
    void applyFrustum() const;

    const FrameData& getFrameData() const;
};

#endif	/* CHANNEL_H */

