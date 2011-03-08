/* 
 * File:   Node.cpp
 * Author: piotrek
 * 
 * Created on 29 listopad 2010, 20:26
 */

#include "Node.h"
#include "Config.h"

bool Node::configInit(const uint32_t initID)
{
   if( !eq::Node::configInit( initID ))
        return false;

    // All render data is static or multi-buffered, we can run asynchronously
    if( getIAttribute( IATTR_THREAD_MODEL ) == eq::UNDEFINED )
        setIAttribute( IATTR_THREAD_MODEL, eq::ASYNC );

    Config* config = static_cast< Config* >( getConfig( ));
    config->mapData( initID );
    return true;
}

