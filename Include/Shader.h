#pragma once

#include <glew.h>
#include "Utility.h"

class Shader{
public:
    Shader(const char* vertexShader, const char* fragmentShader);
    ~Shader();

    void Use();
    unsigned int GetID();

    //
    //Do not use this method with uniforms that contain multiple values - vec3, vec4, ...
    //
    template<typename T>
    int SetUniform(PFNGLUNIFORM1IPROC glUniformFunction, const char* uniformName, T uniformValue){
        GLint loc = glGetUniformLocation(programID, uniformName);
        if(loc == -1){
            print("COULD NOT FIND UNIFORM: ");println(uniformName);
            return 0;
        }
        
        Use();
        
        glUniformFunction(loc, uniformValue);
        return 1;
    }
    int SetUniformMatrix(PFNGLUNIFORMMATRIX4FVPROC glUniformFunction, const char* uniformName, GLsizei count, GLboolean transpose, const GLfloat* uniformValue);
    int SetUniform2f(const char* uniformName, float v1, float v2);
    int SetUniform3f(const char* uniformName, float v1, float v2, float v3);
    int SetUniform4f(const char* uniformName, float v1, float v2, float v3, float v4);
private:
    unsigned int programID;
};