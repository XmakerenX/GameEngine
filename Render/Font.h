#ifndef  _FONT_H
#define  _FONT_H

#include <iostream>
#include <utility>
#include <map>
#include <fstream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <cmath>
#include <string>
#include "Shader.h"
#include "monoBuffer.h"

// Holds all state information relevant to a character glyph as loaded using FreeType
struct CharGlyph {
    GLuint     TextureID;   // ID handle of the glyph texture
    glm::ivec2 Size;        // Size of glyph
    glm::ivec2 Bearing;     // Offset from baseline to left/top of glyph
    GLuint     Advance;     // Horizontal offset to advance to next glyph
};

// stores glpyh buffer data and info, ready to be batched to a single texture
class CharGlyphBat : public monoBuffer
{
public:
    CharGlyphBat() : monoBuffer()
    {
        Bearing_ = {0,0};
        Advance_ = 0;
    }

    CharGlyphBat(const CharGlyphBat& c) : monoBuffer(c.getBuffer(),c.width_,c.height_)
    {
        Bearing_ = c.Bearing_;
        Advance_ = c.Advance_;
    }

    CharGlyphBat(CharGlyphBat&& c)
    {
        buffer_ = c.getBuffer();
        width_ = c.width_;
        height_ = c.height_;
        empty = false;

        Bearing_ = c.Bearing_;
        Advance_ = c.Advance_;

        c.buffer_ = nullptr;
        c.width_ = 0;
        c.height_ = 0;
        c.empty = true;

        c.Bearing_ = glm::ivec2(0,0);
        c.Advance_ = 0;
    }

    ~CharGlyphBat()
    {
        ;
    }

    CharGlyphBat(glm::ivec2 bearing, GLuint advnace)
    {
        Bearing_ = bearing;
        Advance_ = advnace;
    }

    glm::ivec2 Bearing_;     // Offset from baseline to left/top of glyph
    GLuint     Advance_;     // Horizontal offset to advance to next glyph
};

struct FontString {
    GLuint texName;
    GLuint width;
    GLuint height;
};

class mkFont
{
public:
    mkFont(std::__cxx11::string fontName);
    ~mkFont();

    int init(int height);
    void renderText(Shader *shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
    void renderTextBatched(Shader *shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
    std::string getFontPath(std::string fontName);

    void setScreenHeight(int height);

    static void printallFonts();


private:
    std::string fontPath;
    std::map<GLchar, CharGlyph> Characters_;
    std::map<GLchar, CharGlyphBat> NewCharacters_;
    std::map<std::string, FontString> fontTexures_;
    GLuint VAO;
    GLuint VBO;
    GLushort indices[6];
    //TODO: find a way to make font ignorant of screen size
    int height_;

    int maxHeight_;
    int maxOffset_;

    bool cacheTextTexutre(std::string text);
    void cacheGlyth(FT_Library ft, FT_Face face);
    void cacheGlythBatched(FT_Library ft, FT_Face face, int maxHeight, int maxOffset);
};

#endif  //_FONT_H
