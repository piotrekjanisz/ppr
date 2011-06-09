/* 
 * File:   Node.cpp
 * Author: piotrek
 * 
 * Created on 29 listopad 2010, 20:26
 */

#include "Node.h"
#include "Config.h"
#include "data/RandomDataProvider.h"
#include "data/HdfDataProvider.h"
#include <boost/make_shared.hpp>

bool Node::configInit(const eq::uint128_t& initID)
{
   if( !eq::Node::configInit( initID ))
        return false;

    // All render data is static or multi-buffered, we can run asynchronously
    if( getIAttribute( IATTR_THREAD_MODEL ) == eq::UNDEFINED )
        setIAttribute( IATTR_THREAD_MODEL, eq::ASYNC );

    Config* config = static_cast< Config* >( getConfig( ));
    config->mapData( initID );

    InitData initData = config->getInitData();

    const int POS_COMPONENT_NUM = 4;
    const float X_MIN = -20.0f;
    const float X_MAX = 20.0f;
    const float Y_MIN = -20.0f;
    const float Y_MAX = 20.0f;
    const float Z_MIN = 1.0f;
    const float Z_MAX = 40.0f;
    if (initData.getHdfFile().empty()) {
    	_dataProvider = boost::make_shared<RandomDataProvider>(initData.getSphereNum(), POS_COMPONENT_NUM, X_MIN, X_MAX, Y_MIN, Y_MAX, Z_MIN, Z_MAX);
    } else {
    	_dataProvider = boost::make_shared<HdfDataProvider>(initData.getHdfFile().c_str());
    }

    return true;
}

