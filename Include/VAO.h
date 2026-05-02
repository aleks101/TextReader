#pragma once

#include <glew.h>
#include <vector>

struct DataParams{
    GLenum normalised;
    GLint size;
};

class VAO {
public:
    VAO();
    ~VAO();

    void PushDataAttribute(GLint size, GLenum normalised);
    void ResetAttributes();
    void FinishDataArray(const std::vector<float>& vertices, const std::vector<unsigned int>& indices = {}, GLenum renderType = GL_TRIANGLES);

    void Bind() const;
    void Draw() const;

private:
    GLuint vao, vbo, ebo;
    GLenum type;
    bool useEBO = false;
    GLsizei vertexCount;
    GLsizei indexCount;

    int dataCount = 0;
    GLint dataSize = 0;
    std::vector<DataParams> attribes;
};