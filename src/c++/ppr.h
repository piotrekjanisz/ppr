/* 
 * File:   ppr.h
 * Author: piotrek
 *
 * Created on 13 grudzień 2010, 17:30
 */

#ifndef PPR_H
#define	PPR_H

#include <eq/eq.h>
#include "vmmlib/vmmlib.hpp"

namespace ppr {

enum LogTopics
{
  	LOG_GENERAL = eq::LOG_CUSTOM << 0,
};

typedef vmml::matrix<4, 4, float> Matrix4f;


}; // namespace ppr

#endif	/* PPR_H */

