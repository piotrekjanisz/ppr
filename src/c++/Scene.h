/* 
 * File:   Scene.h
 * Author: piotrek
 *
 * Created on 8 grudzień 2010, 15:46
 */

#ifndef SCENE_H
#define	SCENE_H

#include "vmmlib/vmmlib.hpp"

class Scene
{
protected:
    vmml::mat4f _modelMatrix;
    vmml::mat4f _modelViewMatrix;

public:
    Scene();
    virtual ~Scene();
    void render();
private:

};

#endif	/* SCENE_H */

