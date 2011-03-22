/* 
 * File:   Channel.cpp
 * Author: piotrek
 * 
 * Created on 4 listopad 2010, 20:22
 */

#include "Pipe.h"
#include "Channel.h"
#include "glus/Glus.h"
#include "utils.h"
#include <GL/gl.h>
#include <iostream>
#include <eq/eq.h>
#include "ppr.h"
#include "data/HdfDataProvider.h"
#include "data/RandomDataProvider.h"

const int POS_COMPONENT_NUM = 4;

Channel::Channel(eq::Window* parent) : eq::Channel(parent), BATCH_NUM(1000), BATCH_SIZE(1000), OBJ_NUM(BATCH_NUM * BATCH_SIZE), SPHERE_NUM_SLICES(8)
{
    _frameNum = 0.0;
    _measureTime = 5000.0;
    _clock.reset();
    _frameCount = 0;

    _yRotation = 180;
    _zTranslation = -20;

    // loading shader program
    try {
        _shaderProgram.load("shaders/Vertex.vs", "shaders/Fragment.fs");
    } catch (const ShaderException& ex) {
        std::cout << ex.getErrorMessage() << std::endl;
        exit(1); // TODO implement better exiting
    }
    _shaderProgram.useThis();

    // initialize data provider
    const float X_MIN = -20.0f;
    const float X_MAX = 20.0f;
    const float Y_MIN = -20.0f;
    const float Y_MAX = 20.0f;
    const float Z_MIN = 1.0f;
    const float Z_MAX = 40.0f;

    _dataProvider = new RandomDataProvider(OBJ_NUM, POS_COMPONENT_NUM, X_MIN, X_MAX, Y_MIN, Y_MAX, Z_MIN, Z_MAX);
    //_dataProvider = new HdfDataProvider("/media/media/studia/hdf/box_rho.h5");

    // generate and bind VERTEX ARRAY OBJECT
    glGenVertexArrays(1, (GLuint*) & _vao);
    glBindVertexArray(_vao);

    _vertexLocation = glGetAttribLocation(_shaderProgram.getId(), "vertex");
    _projectionMatrixLocation = glGetUniformLocation(_shaderProgram.getId(), "projectionMatrix");
    _modelViewMatrixLocation = glGetUniformLocation(_shaderProgram.getId(), "modelViewMatrix");

    // initialize VBO for vertex data
    glGenBuffers(1, (GLuint*) & _pointsBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, _pointsBufferId);
    glBufferData(GL_ARRAY_BUFFER, _dataProvider->getParticleNum(1.0) * POS_COMPONENT_NUM * sizeof(float), _dataProvider->getPositions(1.0).array, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(_vertexLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(_vertexLocation);

    glBindFragDataLocation(_shaderProgram.getId(), 0, "fragColor");

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    //glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    glEnable(GL_POINT_SPRITE);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
}

Channel::~Channel() { }

void Channel::frameDraw(const uint32_t spin)
{
    FrameData frameData = getFrameData();
    eq::Channel::frameDraw(spin);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
/*
    vmml::identity(_modelMatrix);
    vmml::identity(_modelViewMatrix);
    _modelMatrix.rotate_x(_xRotation);
    _modelMatrix.rotate_y(_yRotation);
    _modelMatrix.set_translation(0.0f, 0.0f, _zTranslation);
    _modelViewMatrix *= frameData.getCameraTransformation();
    _modelViewMatrix *= _modelMatrix;
    glUniformMatrix4fv(_modelViewMatrixLocation, 1, GL_FALSE, _modelViewMatrix.array);
*/

    Glus::glusLoadIdentityf(_modelMatrix);
    Glus::glusLoadIdentityf(_modelViewMatrix);
    Glus::glusTranslatef(_modelMatrix, 0.0f, 0.0f, _zTranslation);
    Glus::glusRotateRzRyRxf(_modelMatrix, _xRotation, _yRotation, 0.0f);
    Glus::glusMultMatrixf(_modelViewMatrix, _modelViewMatrix, frameData.getCameraTransformation().array);
    Glus::glusMultMatrixf(_modelViewMatrix, _modelViewMatrix, _modelMatrix);
    glUniformMatrix4fv(_modelViewMatrixLocation, 1, GL_FALSE, _modelViewMatrix);

    glBindBuffer(GL_ARRAY_BUFFER, _pointsBufferId);
    glDrawArrays(GL_POINTS, 0, _dataProvider->getParticleNum(_frameNum));

    _frameNum += 0.05;

    _frameCount++;
    _time = _clock.getTimed();
    if (_time > _measureTime) {
        std::cout << (_frameCount / _time)*1000 << "fps" << std::endl;
        _frameCount = 0;
        _clock.reset();
    }
}

void Channel::applyFrustum() const
{
    eq::Frustumf frustum = getFrustum();
    frustum.compute_matrix(_projectionMatrix);
    glUniformMatrix4fv(_projectionMatrixLocation, 1, GL_FALSE, _projectionMatrix.array);
}

const FrameData& Channel::getFrameData() const
{
    const Pipe* pipe = static_cast< const Pipe* >( getPipe( ));
    return pipe->getFrameData();
}
