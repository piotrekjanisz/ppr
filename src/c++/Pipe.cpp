/* 
 * File:   Pipe.cpp
 * Author: piotrek
 * 
 * Created on 28 listopad 2010, 19:48
 */

#include "Pipe.h"

Pipe::Pipe(eq::Node* parent)
    :eq::Pipe(parent) {}

Pipe::~Pipe() { }

bool Pipe::configInit( const uint32_t initID )
{
    if( !eq::Pipe::configInit( initID ))
        return false;

    Config*         config      = static_cast<Config*>( getConfig( ));
    const InitData& initData    = config->getInitData();
    const uint32_t  frameDataID = initData.getFrameDataId();

    const bool mapped = config->mapObject( &_frameData, frameDataID );
    EQASSERT( mapped );

    return mapped;
}

void Pipe::frameStart( const uint32_t frameID, const uint32_t frameNumber )
{
    eq::Pipe::frameStart( frameID, frameNumber );
    _frameData.sync( frameID );
}



