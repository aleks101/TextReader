#include "Shader.h"
#include <iostream>

void PrintErrors(unsigned int shader){
    int  success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }  
}

Shader::Shader(const char* vertexShaderFile, const char* fragmentShaderFile){
    std::string vertexCode = get_file_content(vertexShaderFile);
    std::string fragmentCode = get_file_content(fragmentShaderFile);

    const char* vertexContent = vertexCode.c_str();
    const char* fragmentContent = fragmentCode.c_str();


    //ustvari shader objekt za vertex in fragment
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    //vertex in fragment shader objektu dodaj kodo
    glShaderSource(vertexShader, 1, &vertexContent, NULL);
    glShaderSource(fragmentShader, 1, &fragmentContent, NULL);
    //compile vertex in fragment shaderja in izpisi errorje
    glCompileShader(vertexShader);
    PrintErrors(vertexShader);
    glCompileShader(fragmentShader);
    PrintErrors(fragmentShader);

    programID = glCreateProgram();
    //dodaj programu nasa shaderja
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    glLinkProgram(programID);

    int  success;
    char infoLog[512];

    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(programID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}
Shader::~Shader(){
    glDeleteProgram(programID);
}

void Shader::Use(){
    glUseProgram(programID);
}
unsigned int Shader::GetID(){
    return programID;
}
int Shader::SetUniform2f(const char* uniformName, float v1, float v2){
    unsigned int loc = glGetUniformLocation(programID, uniformName);
    if(loc == -1){
        std::cout<<"COULD NOT FIND UNIFORM: "<< uniformName<<std::endl;
        return 0;
    }

    Use();

    glUniform2f(loc, v1, v2);
    return 1;
}
int Shader::SetUniform3f(const char* uniformName, float v1, float v2, float v3){
    unsigned int loc = glGetUniformLocation(programID, uniformName);
    if(loc == -1){
        std::cout<<"COULD NOT FIND UNIFORM: "<< uniformName<<std::endl;
        return 0;
    }

    Use();

    glUniform3f(loc, v1, v2, v3);
    return 1;
}
int Shader::SetUniform4f(const char* uniformName, float v1, float v2, float v3, float v4){
    unsigned int loc = glGetUniformLocation(programID, uniformName);
    if(loc == -1){
        std::cout<<"COULD NOT FIND UNIFORM: "<< uniformName<<std::endl;
        return 0;
    }

    Use();

    glUniform4f(loc, v1, v2, v3, v4);
    return 1;
}
int Shader::SetUniformMatrix(PFNGLUNIFORMMATRIX4FVPROC glUniformFunction, const char* uniformName, GLsizei count, GLboolean transpose, const GLfloat* uniformValue){
    GLint loc = glGetUniformLocation(programID, uniformName);
    if(loc == -1){
        print("COULD NOT FIND UNIFORM: ");println(uniformName);
        return 0;
    }

    Use();

    glUniformFunction(loc, count, transpose, uniformValue);

    return 1;
}