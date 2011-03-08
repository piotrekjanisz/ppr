/* 
 * File:   Node.h
 * Author: piotrek
 *
 * Created on 29 listopad 2010, 20:26
 */

#ifndef NODE_H
#define	NODE_H

#include <eq/eq.h>

class Node : public eq::Node
{
public:
    Node( eq::Config* parent ) : eq::Node( parent ) {}

protected:
    virtual ~Node() {}
    virtual bool configInit( const uint32_t initID );
private:
};

#endif	/* NODE_H */

