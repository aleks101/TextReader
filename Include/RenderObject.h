#pragma once

#include "Renderable.h"
#include "Utility.h"
#include "Shader.h"

#include <glm/glm.hpp>

class RenderRect : public Renderable{
public:
    RenderRect();
    RenderRect(Shader* shader, Rect rect);
    RenderRect(const RenderRect& obj);
    RenderRect& operator=(const RenderRect& obj);

    virtual ~RenderRect();
    virtual void SetColor(ColorRGB color);
    virtual void SetRect(Rect rect);
    virtual void SetPosition(Vec2 position);
    virtual void Update();
    virtual void Render();
protected:
    Shader* m_shader;
    Rect m_rect;

    ColorRGB m_color;
    glm::mat4 m_translation;

private:
};