#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H  
#include <map>
#include <glm/glm.hpp>

#include "Shader.h"

struct Character {
    unsigned int TextureID;  // ID handle of the glyph texture
    glm::ivec2   Size;       // Size of glyph
    glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};

class Text{
public:
    static void InitClass();
    Text(Shader* shader);
    ~Text();
    void LoadFont(const char* fontPath, int size);
    void Render(std::string text, Vec2 pos, float scale, ColorRGB color);
private:
    static unsigned vao, vbo;
private:
    std::map<char, Character> Characters;
    Shader* m_shader;
};