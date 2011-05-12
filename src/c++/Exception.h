/* 
 * File:   Exception.h
 * Author: piotrek
 *
 * Created on 19 listopad 2010, 17:38
 */

#ifndef EXCEPTION_H_
#define	EXCEPTION_H_

#include <string>
#include <sstream>


class Exception
{
    std::ostringstream _errorMessage;
public:
    Exception(const std::string errorMessage, const std::string& file, int line)
    {
        _errorMessage << errorMessage << "\n\tat" << file << ":" << line;
    }
    virtual ~Exception() {}

    Exception(const Exception& exception)
    {
        _errorMessage << exception.getErrorMessage();
    }

    Exception& operator=(const Exception& exception)
    {
        _errorMessage << exception.getErrorMessage();
        return *this;
    }

    const std::string getErrorMessage() const {
        return _errorMessage.str();
    }
};

#define THROW(exception, message) throw (exception(message, __FILE__, __LINE__))

#endif	/* EXCEPTION_H */

