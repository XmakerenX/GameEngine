/* * GameEngine - A cross platform game engine made using OpenGL and c++
 * Copyright (C) 2016-2020 Matan Keren <xmakerenx@gmail.com>
 *
 * This file is part of GameEngine.
 *
 * GameEngine is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GameEngine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GameEngine.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef  _SPRITE_H
#define _SPRITE_H

#include <vector>
#include <list>
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include "RenderTypes.h"
#include "Shader.h"

struct Texture
{
    Texture()
        :name(0), width(0), height(0)
    {}
    
    Texture(GLuint _name, GLuint _width, GLuint _height)
        :name(_name), width(_width), height(_height)
    {}

    GLuint name;
    GLuint width;
    GLuint height;
};

struct VertexSprite
{
    VertexSprite(float fX, float fY, float fZ, const glm::vec4& diffuseCOlor, float ftu = 0.0f, float ftv = 0.0f)
    {
        pos.x = fX;
        pos.y = fY;
        pos.z = fZ;
        pos.w = 1;
        diffuse = diffuseCOlor;
        uv.x = ftu;
        uv.y = ftv;
    }

    glm::vec4 pos;
    glm::vec4 diffuse;
    glm::vec2 uv;
};

struct StreamOfVertices
{
    StreamOfVertices(const Texture& texture);
    void addQuad(const Rect &spriteRect, const Rect &texRect, const glm::vec4 &tintColor, Point scale);

    Texture texture;

    std::vector<VertexSprite> vertices;
    std::vector<VertexIndex> indices;
};

class Sprite
{
public:
    enum STREAMTYPE{BACKGROUND, REGULAR, HIGHLIGHT, TOP, STREAMTYPE_MAX};
    static const GLuint MAX_QUADS = 20000;

    Sprite();
    ~Sprite();

    bool AddTintedQuad(const Rect& spriteRect, const glm::vec4& tintColor);
    bool AddTexturedQuad(const Rect& spriteRect, const Texture& texture, const Rect &texRect);
    bool AddTintedTexturedQuad(const Rect &spriteRect, glm::vec4 tintColor, const Texture& texture, const Rect &texRect = EMPTY_RECT);
    bool AddQuad(const Rect &spriteRect, glm::vec4 tintColor, const Texture& texture, const Rect &texRect, Point scale);
    void Clear();

    bool Init();
    bool Render(Shader *shader);

private:

    GLuint m_vertexArrayObject;
    GLuint m_vertexBuffer;
    GLuint m_indicesBuffer;

    std::vector<StreamOfVertices> m_vertexStreams;

    float m_fScaleWidth;
    float m_fScaleHeight;
};

#endif  //_SPRITE_H
