#include "VAO.h"
#include <iostream>
VAO::VAO() {}
VAO::~VAO(){
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}

void VAO::PushDataAttribute(GLint size, GLenum normalised){
    dataCount++;
    dataSize+=size;

    DataParams params;
    params.normalised = normalised;
    params.size = size;
    attribes.push_back(params);
}
void VAO::ResetAttributes(){
    dataCount = 0;
    dataSize = 0;
    attribes.clear();
}
void VAO::FinishDataArray(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, GLenum renderType){
    type = renderType;
    if(attribes.empty())
        return;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
                    vertices.data(), GL_STATIC_DRAW);

    if (!indices.empty()) {
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                        indices.data(), GL_STATIC_DRAW);
        useEBO = true;
        indexCount = indices.size();
    }
    int offset = 0;
    for(int i=0;i<attribes.size();i++){
        glVertexAttribPointer(i, attribes[i].size, GL_FLOAT, attribes[i].normalised, dataSize * sizeof(float), (void*)(offset*sizeof(float)));
        glEnableVertexAttribArray(i);
        offset = attribes[i].size;
    }
    glBindVertexArray(0); // unbind
}

void VAO::Bind() const { 
    glBindVertexArray(vao); 
}
void VAO::Draw() const {
    if (useEBO) {
        glDrawElements(type, indexCount, GL_UNSIGNED_INT, 0);
    } else {
        glDrawArrays(type, 0, vertexCount);
    }
}