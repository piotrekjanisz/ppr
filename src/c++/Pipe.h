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
#include "data/DataProvider.h"

class Pipe : public eq::Pipe
{
public:
    Pipe(eq::Node* parent);
    virtual ~Pipe();

    virtual bool configInit( const eq::uint128_t& initID );
    virtual void frameStart( const eq::uint128_t& frameID, const uint32_t frameNumber );

    const FrameData& getFrameData() const { return _frameData; }
    const DataProvider* getDataProvider() const { return _dataProvider; }
private:
    FrameData _frameData;
    DataProvider* _dataProvider;
};

#endif	/* PIPE_H */

