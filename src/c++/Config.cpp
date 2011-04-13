/* 
 * File:   Config.cpp
 * Author: piotrek
 * 
 * Created on 28 listopad 2010, 17:04
 */

#include "Config.h"
#include <iostream>

Config::Config(eq::base::RefPtr< eq::Server > parent)
: eq::Config(parent), _modelTransform(vmml::mat4f::IDENTITY), _speed(0.2f) { }

Config::~Config() { }

bool Config::init()
{
    M3DMatrix44f transform;
    _cameraFrame.GetCameraMatrix(transform, false);
    _frameData.setCameraTransformation(transform);
    _cameraFrame.GetCameraMatrix(transform, true);
    _frameData.setCameraRotation(transform);
    _frameData.setModelTransformation(_modelTransform);
    _frameData.setLightDirection(vmml::vec4f(-1.0f, -1.0f, -1.0f, 1.0f));

    registerObject(&_frameData);
    _frameData.setAutoObsolete(getLatency());

    _initData.setFrameDataId(_frameData.getID());
    registerObject(&_initData);

    if (!eq::Config::init(_initData.getID())) {
        return false;
    }
    return true;
}

uint32_t Config::startFrame()
{
    M3DMatrix44f transform;
    _cameraFrame.GetCameraMatrix(transform, false);
    _frameData.setCameraTransformation(transform);
    _cameraFrame.GetCameraMatrix(transform, true);
    _frameData.setCameraRotation(transform);
    _frameData.setModelTransformation(_modelTransform);
    const uint32_t version = _frameData.commit();
    return eq::Config::startFrame(version);
}

bool Config::handleEvent(const eq::ConfigEvent* event)
{
    switch (event->data.type) {
        case eq::Event::KEY_PRESS:
            if (handleKeyEvent(event->data.keyPress))
                return true;
            break;
        case eq::Event::POINTER_MOTION:
            if (event->data.pointerMotion.buttons == eq::PTR_BUTTON1) {
                _cameraFrame.RotateLocalY(-0.005f * event->data.pointerMotion.dx);
                _cameraFrame.RotateLocalX(-0.005f * event->data.pointerMotion.dy);
                return true;
            } else if (event->data.pointerMotion.buttons == eq::PTR_BUTTON3) {
            	_modelTransform.rotate_y(-0.005f * event->data.pointerMotion.dx);
            	_modelTransform.rotate_x(-0.005f * event->data.pointerMotion.dy);
            	return true;
            }
            break;

    }
    return eq::Config::handleEvent(event);
}

bool Config::handleKeyEvent(const eq::KeyEvent& event)
{
    switch (event.key) {
        case eq::KC_RIGHT:
        case 'd':
            _cameraFrame.MoveRight(-_speed);
            return true;
        case eq::KC_LEFT:
        case 'a':
            _cameraFrame.MoveRight(_speed);
            return true;
        case eq::KC_UP:
        case 'w':
            _cameraFrame.MoveForward(_speed);
            return true;
        case eq::KC_DOWN:
        case 's':
            _cameraFrame.MoveForward(-_speed);
            return true;
    }
    return false;
}

void Config::mapData(const uint32_t initDataID)
{
    if( _initData.getID() == EQ_ID_INVALID ) {
        EQCHECK( mapObject( &_initData, initDataID ));
        unmapObject( &_initData ); // data was retrieved, unmap immediately
    } else { // appNode, _initData is registered already
        EQASSERT( _initData.getID() == initDataID );
    }
}


