/* 
 * File:   Pipe.h
 * Author: piotrek
 *
 * Created on 28 listopad 2010, 19:48
 */

#ifndef PIPE_H
#define	PIPE_H

#include <eq/eq.h>
#include "Config.h"
#include "FrameData.h"

class Pipe : public eq::Pipe
{
public:
    Pipe(eq::Node* parent);
    virtual ~Pipe();

    virtual bool configInit( const uint32_t initID );
    virtual void frameStart( const uint32_t frameID, const uint32_t frameNumber );

    const FrameData& getFrameData() const { return _frameData; }
private:
    FrameData _frameData;
};

#endif	/* PIPE_H */

