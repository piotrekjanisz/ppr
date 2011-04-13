/* 
 * File:   Node.h
 * Author: piotrek
 *
 * Created on 29 listopad 2010, 20:26
 */

#ifndef NODE_H
#define	NODE_H

#include <eq/eq.h>
#include <boost/shared_ptr.hpp>
#include "data/DataProvider.h"


class Node : public eq::Node
{
public:
    Node( eq::Config* parent ) : eq::Node( parent ) {}

    boost::shared_ptr<DataProvider> getDataProvider() { return _dataProvider; }

protected:
    virtual ~Node() {}
    virtual bool configInit( const uint32_t initID );
private:
    boost::shared_ptr<DataProvider> _dataProvider;
};

#endif	/* NODE_H */

