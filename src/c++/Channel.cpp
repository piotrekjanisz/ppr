/* 
 * File:   Channel.cpp
 * Author: piotrek
 * 
 * Created on 4 listopad 2010, 20:22
 */

#include "Pipe.h"
#include "Node.h"
#include "Channel.h"
#include "glus/Glus.h"
#include "utils.h"
#include "ppr.h"
#include "data/HdfDataProvider.h"
#include "data/RandomDataProvider.h"
#include <GL/gl.h>
#include <iostream>
#include <eq/eq.h>
#include <cstring>
#include <boost/shared_ptr.hpp>

const int POS_COMPONENT_NUM = 4;

Channel::Channel(eq::Window* parent) : eq::Channel(parent)
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
        _vertexLocation = _shaderProgram.getAttribLocation("vertex");
        _projectionMatrixLocation = _shaderProgram.getUniformLocation("projectionMatrix");
        _modelViewMatrixLocation = _shaderProgram.getUniformLocation("modelViewMatrix");
        _lightPositionLocation = _shaderProgram.getUniformLocation("lightPosition");
    } catch (const ShaderException& ex) {
        std::cout << ex.getErrorMessage() << std::endl;
        exit(1); // TODO implement better exiting
    }
    _shaderProgram.useThis();

    Node* node = static_cast<Node*>(getNode());
    _dataProvider = node->getDataProvider();

    // generate and bind VERTEX ARRAY OBJECT
    glGenVertexArrays(1, (GLuint*) & _vao);
    glBindVertexArray(_vao);

    // initialize VBO for vertex data
    glGenBuffers(1, (GLuint*) & _pointsBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, _pointsBufferId);
    glBufferData(GL_ARRAY_BUFFER, _dataProvider->getParticleNum(1.0) * POS_COMPONENT_NUM * sizeof(float), _dataProvider->getPositions(1.0).array, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(_vertexLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(_vertexLocation);

    glBindFragDataLocation(_shaderProgram.getId(), 0, "fragColor");

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_POINT_SPRITE);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
}

Channel::~Channel() { }

void Channel::frameDraw(const uint32_t spin)
{
    FrameData frameData = getFrameData();
    eq::Channel::frameDraw(spin);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Glus::glusLoadIdentityf(_modelViewMatrix);
    Glus::glusMultMatrixf(_modelViewMatrix, _modelViewMatrix, frameData.getCameraTransformation().array);
    Glus::glusMultMatrixf(_modelViewMatrix, _modelViewMatrix, frameData.getModelTransformation().array);
    glUniformMatrix4fv(_modelViewMatrixLocation, 1, GL_FALSE, _modelViewMatrix);
    glUniform4fv(_lightPositionLocation, 1, frameData.getLightPositionInCameraSpace().array);

    boost::shared_ptr<Step> step = _dataProvider->getStep(_frameNum, 0.0, 1.0, true);
    glBindBuffer(GL_ARRAY_BUFFER, _pointsBufferId);
    glBufferData(GL_ARRAY_BUFFER, step->getParticlesNumber() * Step::COORDINATES_NUMBER * sizeof(float), step->getCoordinates(), GL_DYNAMIC_DRAW);
    glDrawArrays(GL_POINTS, 0, step->getParticlesNumber());
    _frameNum += 0.05;

    measureFrameCount();
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
