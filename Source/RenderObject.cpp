#include "RenderObject.h"

#include "RenderManager.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

RenderRect::RenderRect() : Renderable(CoreRenderType::triangle) {}
RenderRect::RenderRect(Shader* shader, Rect rect) : m_shader(shader), m_rect(rect), Renderable(CoreRenderType::triangle){
}
RenderRect::RenderRect(const RenderRect& obj) : m_shader(obj.m_shader), m_rect(obj.m_rect), Renderable(CoreRenderType::triangle) {
    m_color = obj.m_color;
    m_translation = obj.m_translation;
}
RenderRect& RenderRect::operator=(const RenderRect& obj) {
    if (this == &obj)
        return *this;

    this->m_shader = obj.m_shader;
    this->m_rect = obj.m_rect;
    this->m_color = obj.m_color;
    this->m_translation = obj.m_translation;
    return *this;
}
RenderRect::~RenderRect(){

}
void RenderRect::SetColor(ColorRGB color){
    m_color = color;
}
void RenderRect::SetRect(Rect rect){
    m_rect = rect;
}
void RenderRect::SetPosition(Vec2 position){
    m_rect.x = position.x;
    m_rect.y = position.y;
}
void RenderRect::Update(){
    float drawW = (float)m_rect.w;
    float drawH = (float)m_rect.h;

    m_translation = glm::mat4(1.0f);
    m_translation = glm::translate(m_translation, glm::vec3((float)m_rect.x, (float)m_rect.y, 0.0f));
    m_translation = glm::scale(m_translation, glm::vec3(drawW, drawH, 1.0f));

    SubmitRenderable((Renderable*)this);
}
void RenderRect::Render(){
    if (m_shader != nullptr){
        m_shader->Use();
        m_shader->SetUniformMatrix(glUniformMatrix4fv, "transform", 1, GL_FALSE, glm::value_ptr(m_translation));
        m_shader->SetUniform3f("ourColor", m_color.R,m_color.G,m_color.B);
    }
}