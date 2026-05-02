#pragma once

#include <glew.h>

enum class CoreRenderType {triangle, point, line, text};

class Renderable{
public:
    Renderable(CoreRenderType type) : renderType(type) {}
    virtual void Render() = 0;
public:
    CoreRenderType renderType;
    int vaoID;
};