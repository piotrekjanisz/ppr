/* 
 * File:   ShaderProgram.cpp
 * Author: piotrek
 * 
 * Created on 19 listopad 2010, 16:09
 */

#include "eq/eq.h"
#include "GlExtensions.h"
#include "ShaderProgram.h"
#include "GL/gl.h"
#include <fstream>

using namespace std;

ShaderProgram::ShaderProgram()
: _vertexProgram(0), _fragmentProgram(0), _geometryProgram(0) { }

void ShaderProgram::load(const std::string& vertexSource, const std::string& fragmentSource) throw (ShaderException)
{
    loadAux(vertexSource, fragmentSource, "");
    glLinkProgram(_programId);

    int linked;
    glGetProgramiv(_programId, GL_LINK_STATUS, &linked);

    if (!linked) {
        int logLength;
        glGetProgramiv(_programId, GL_INFO_LOG_LENGTH, &logLength);

        char* log = new char[logLength];
        string logStr(log);
        delete[] log;

        int charsWritten;
        glGetProgramInfoLog(_programId, logLength, &charsWritten, log);

        THROW(ShaderException, string("error while linking shader: \n") + logStr);
    }
}

void ShaderProgram::load(const std::string& vertexSource, const std::string& fragmentSource, const std::string& geometrySource) throw (ShaderException)
{
    loadAux(vertexSource, fragmentSource, geometrySource);
}

void ShaderProgram::loadAux(const std::string& vertexSoruce, const std::string& fragmentSource, const std::string& geometrySource) throw (ShaderException)
{
    if (!vertexSoruce.empty()) {
        _vertexProgram = loadShader(vertexSoruce, GL_VERTEX_SHADER);
    }

    if (!fragmentSource.empty()) {
        _fragmentProgram = loadShader(fragmentSource, GL_FRAGMENT_SHADER);
    }

    if (!geometrySource.empty()) {
        _geometryProgram = loadShader(geometrySource, GL_GEOMETRY_SHADER);
    }

    _programId = glCreateProgram();
    if (_vertexProgram)
        glAttachShader(_programId, _vertexProgram);

    if (_fragmentProgram)
        glAttachShader(_programId, _fragmentProgram);

    if (_geometryProgram)
        glAttachShader(_programId, _geometryProgram);
}

int ShaderProgram::loadShader(const std::string& sourcePath, int shaderType) throw (ShaderException)
{
    fstream sourceStream(sourcePath.c_str(), ios_base::in);
    int retVal = 0;
    if (sourceStream.is_open()) {
        std::string source((std::istreambuf_iterator<char>(sourceStream)), std::istreambuf_iterator<char>());
        retVal = glCreateShader(shaderType);
        const char* src = const_cast<char*> (source.c_str());
        glShaderSource(retVal, 1, &src, 0);
        glCompileShader(retVal);
        int compiled;
        glGetShaderiv(retVal, GL_COMPILE_STATUS, &compiled);
        if (!compiled) {
            int logLength;
            glGetShaderiv(retVal, GL_INFO_LOG_LENGTH, &logLength);
            char* log = new char[logLength];
            int charsWritten;
            glGetShaderInfoLog(retVal, logLength, &charsWritten, log);
            string logStr(log);
            delete [] log;
            THROW(ShaderException, (string("Error while compiling ") + sourcePath + string(": ") + logStr));
        }
    } else {
        THROW(ShaderException, (string("Error while opening file: ") + sourcePath));
    }
    return retVal;
}

ShaderProgram::~ShaderProgram()
{
    if (_programId)
        glDeleteProgram(_programId);
    if (_vertexProgram)
        glDeleteShader(_vertexProgram);
    if (_fragmentProgram)
        glDeleteShader(_fragmentProgram);
    if (_geometryProgram)
        glDeleteShader(_geometryProgram);
}

void ShaderProgram::useThis() const
{
    glUseProgram(getId());
}

void ShaderProgram::useNone()
{
    glUseProgram(0);
}
