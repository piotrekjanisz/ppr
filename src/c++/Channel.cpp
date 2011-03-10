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

Channel::Channel(eq::Window* parent) : eq::Channel(parent), BATCH_NUM(10), BATCH_SIZE(1000), OBJ_NUM(BATCH_NUM * BATCH_SIZE), SPHERE_NUM_SLICES(8)
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
        EQLOG(LOG_GENERAL) << ex.getErrorMessage() << std::endl;
        exit(1); // TODO implement better exiting
    }
    _shaderProgram.useThis();

    // bind instanceData uniform
    glUniformBlockBinding(_shaderProgram.getId(), glGetUniformBlockIndex(_shaderProgram.getId(), "instanceData"), 0);

    // generate and bind VERTEX ARRAY OBJECT
    glGenVertexArrays(1, (GLuint*) & _vao);
    glBindVertexArray(_vao);

    _vertexLocation = glGetAttribLocation(_shaderProgram.getId(), "vertex");
    _colorLocation = glGetAttribLocation(_shaderProgram.getId(), "color");
    _projectionMatrixLocation = glGetUniformLocation(_shaderProgram.getId(), "projectionMatrix");
    _modelViewMatrixLocation = glGetUniformLocation(_shaderProgram.getId(), "modelViewMatrix");
    _normalLocation = glGetAttribLocation(_shaderProgram.getId(), "normal");

    Glus::GLUSshape sphere;
    Glus::glusCreateSpheref(&sphere, 0.2f, SPHERE_NUM_SLICES);
    _indicesNumber = sphere.numberIndices;

    // initialize VBO for vertex data
    int vertexBufferId;
    glGenBuffers(1, (GLuint*) & vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, sphere.numberVertices * 4 * sizeof (GLfloat), (GLfloat*) sphere.vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(_vertexLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

    // initialize VBO for normal data
    int normalBufferId;
    glGenBuffers(1, (GLuint*) & normalBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, normalBufferId);
    glBufferData(GL_ARRAY_BUFFER, sphere.numberVertices * 3 * sizeof (GLfloat), (GLfloat*) sphere.normals, GL_STATIC_DRAW);
    glVertexAttribPointer(_normalLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // create uniform buffer and store instance data
    glGenBuffers(1, (GLuint*) & _instanceDataUBO);
    glBindBuffer(GL_UNIFORM_BUFFER, _instanceDataUBO);
    glBufferData(GL_UNIFORM_BUFFER, BATCH_SIZE * POS_COMPONENT_NUM * sizeof (float), 0, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, _instanceDataUBO);

    const float X_MIN = -20.0f;
    const float X_MAX = 20.0f;
    const float Y_MIN = -20.0f;
    const float Y_MAX = 20.0f;
    const float Z_MIN = 1.0f;
    const float Z_MAX = 40.0f;

    //_dataProvider = new RandomDataProvider(OBJ_NUM, POS_COMPONENT_NUM, X_MIN, X_MAX, Y_MIN, Y_MAX, Z_MIN, Z_MAX);
    _dataProvider = new HdfDataProvider("/media/media/studia/hdf/box_rho.h5");
    int instancesCoordsBO;

    // initialize VBO for indices
    int indicesBufferId;
    glGenBuffers(1, (GLuint*) & indicesBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphere.numberIndices * sizeof (GLuint), (GLuint*) sphere.indices, GL_STATIC_DRAW);


    glBindFragDataLocation(_shaderProgram.getId(), 0, "fragColor");
    glEnableVertexAttribArray(_vertexLocation);
    glEnableVertexAttribArray(_colorLocation);
    glEnableVertexAttribArray(_normalLocation);
    // detach current VAO
    glBindVertexArray(0);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    _cameraFrame = CameraFrame(vmml::vec3d(0, 1, 0), vmml::vec3d(0, 0, 1), vmml::vec3d(0, 0, -1));
}

Channel::~Channel() { }

void Channel::frameDraw(const uint32_t spin)
{
    FrameData frameData = getFrameData();
    eq::Channel::frameDraw(spin);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Glus::glusLoadIdentityf(_modelMatrix);
    Glus::glusLoadIdentityf(_modelViewMatrix);
    Glus::glusTranslatef(_modelMatrix, 0.0f, 0.0f, _zTranslation);
    Glus::glusRotateRzRyRxf(_modelMatrix, _xRotation, _yRotation, 0.0f);
    
    Glus::glusMultMatrixf(_modelViewMatrix, _modelViewMatrix, frameData.getCameraTransformation().array);
    Glus::glusMultMatrixf(_modelViewMatrix, _modelViewMatrix, _modelMatrix);
    glUniformMatrix4fv(_modelViewMatrixLocation, 1, GL_FALSE, _modelViewMatrix);

    Array<float> data = _dataProvider->getPositions(_frameNum);
    for (int i = 0; i < BATCH_NUM; i++) {
        glBindVertexArray(_vao);
        glBindBuffer(GL_UNIFORM_BUFFER, _instanceDataUBO);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, BATCH_SIZE * POS_COMPONENT_NUM * sizeof (float), &data.array[i * BATCH_SIZE * POS_COMPONENT_NUM]);
        glDrawElementsInstanced(GL_TRIANGLES, _indicesNumber, GL_UNSIGNED_INT, 0, BATCH_SIZE);
        glBindVertexArray(0);
    }

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
    Glus::glusFrustumf((Glus::GLUSfloat*) _projectionMatrix, frustum.left(), frustum.right(), frustum.bottom(), frustum.top(), frustum.near_plane(), frustum.far_plane());
    glUniformMatrix4fv(_projectionMatrixLocation, 1, GL_FALSE, _projectionMatrix);
}

const FrameData& Channel::getFrameData() const
{
    const Pipe* pipe = static_cast< const Pipe* >( getPipe( ));
    return pipe->getFrameData();
}
