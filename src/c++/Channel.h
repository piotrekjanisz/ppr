/* 
 * File:   Channel.h
 * Author: piotrek
 *
 * Created on 4 listopad 2010, 20:22
 */

#ifndef CHANNEL_H
#define	CHANNEL_H

#include <eq/eq.h>
#include <boost/shared_ptr.hpp>
#include "glus/Glus.h"
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
    GLfloat _modelMatrix[16];
    GLfloat _modelViewMatrix[16];

    mutable ppr::Matrix4f _projectionMatrix;

    int _pointsBufferId;
    int _vertexLocation;
    int _lightPositionLocation;
    int _pointSizeLocation;
    int _projectionMatrixLocation;
    int _modelViewMatrixLocation;
    int _vao;
    int _instanceDataUBO;

    ShaderProgram _shaderProgram;

    boost::shared_ptr<DataProvider> _dataProvider;
    int _indicesNumber;

    float _eyeX;
    float _eyeY;
    float _eyeZ;
    float _xRotation;
    float _yRotation;
    float _zTranslation;

    double _time;
    double _updateFpsTime;
    co::base::Clock _clock;

    double _frameNum;

    inline void displayFrameRate();


protected:
    void frameDraw(const eq::uint128_t& spin);
    void applyFrustum() const;

    const FrameData& getFrameData() const;
};

inline void Channel::displayFrameRate()
{
	_time = _clock.getTimed();
	if (_time > _updateFpsTime) {
		_clock.reset();
		std::cout << getWindow()->getFPS() << "fps" << std::endl;
	}
}

#endif	/* CHANNEL_H */

