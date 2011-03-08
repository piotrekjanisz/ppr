/* 
 * File:   FrameData.h
 * Author: piotrek
 *
 * Created on 15 listopad 2010, 20:08
 */

#ifndef FRAMEDATA_H
#define	FRAMEDATA_H

#include "eq/eq.h"

class FrameData : public eq::Object
{
public:
    virtual ~FrameData();

    void setCameraTransformation(const eq::Matrix4f& matrix)
    {
        setDirty(DIRTY_CAMERA);
        _cameraTransformation = matrix;
    }

    const eq::Matrix4f& getCameraTransformation() const { return _cameraTransformation; }

protected:
    virtual void serialize(eq::net::DataOStream& os,
                           const uint64_t dirtyBits);

    virtual void deserialize(eq::net::DataIStream& is,
                             const uint64_t dirtyBits);

    enum DirtyBits
    {
        DIRTY_CAMERA = eq::Object::DIRTY_CUSTOM << 0,
    };

private:
    eq::Matrix4f _cameraTransformation;
};

#endif	/* FRAMEDATA_H */

