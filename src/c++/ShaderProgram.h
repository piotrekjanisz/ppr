/* 
 * File:   ShaderProgram.h
 * Author: piotrek
 *
 * Created on 19 listopad 2010, 16:09
 */

#ifndef SHADERPROGRAM_H
#define	SHADERPROGRAM_H

#include <string>
#include "Exception.h"

class ShaderException : public Exception
{
public:
    ShaderException(const std::string& errorMessage, const std::string& file, int line)
        : Exception(errorMessage, file, line)
    {}
};

class ShaderProgram
{
public:
    ShaderProgram();
    void load(const std::string& vertexSource, const std::string& fragmentSource) throw(ShaderException);
    void load(const std::string& vertexSource, const std::string& fragmentSource, const std::string& geometrySource) throw(ShaderException);
    virtual ~ShaderProgram();

    /**
     * @return opengl shader program id
     */
    int getId() const { return _programId; }

    /**
     * Binds this program
     */
    void useThis() const;

    /**
     * Unbinds any bind program
     */
    static void useNone();

    int getAttribLocation(const char* name);

    int getUniformLocation(const char* name);
private:
    void loadAux(const std::string& vertexSoruce, const std::string& fragmentSource, const std::string& geometrySource) throw(ShaderException);
    int loadShader(const std::string& source, int shaderType) throw(ShaderException);

    int _programId;
    int _vertexProgram;
    int _fragmentProgram;
    int _geometryProgram;
};

#endif	/* SHADERPROGRAM_H */

