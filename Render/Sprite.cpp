//
// GameEngine - A cross platform game engine made using OpenGL and c++
// Copyright (C) 2016-2020 Matan Keren <xmakerenx@gmail.com>
//
// This file is part of GameEngine.
//
// GameEngine is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// GameEngine is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with GameEngine.  If not, see <http://www.gnu.org/licenses/>.
//

#include "Sprite.h"
#include <iostream>

//-----------------------------------------------------------------------------
// Name : StreamOfVertices (constructor)
//-----------------------------------------------------------------------------
StreamOfVertices::StreamOfVertices(const Texture& _texture)
{
    texture = _texture;
}

//-----------------------------------------------------------------------------
// Name : addQuad
//-----------------------------------------------------------------------------
void StreamOfVertices::addQuad(const Rect& spriteRect, const Rect& texRect, const glm::vec4& tintColor, Point scale)
{
    float textureRectWidth, textureRectHeight;
    int textureWidth, textureHeight;
    float startU, startV, widthU, heightV;
    startU = startV = widthU = heightV = 0;

    // calculate how much to scale  the UV coordinates of the texture to fit the texRect
    if (texture.name != 0)
    {
        // get the texture width and height
        if (glGetTextureLevelParameteriv != nullptr)
        {
            glGetTextureLevelParameteriv(texture.name, 0, GL_TEXTURE_WIDTH, &textureWidth);
            glGetTextureLevelParameteriv(texture.name, 0, GL_TEXTURE_HEIGHT, &textureHeight);
        }
        else
        {
            textureWidth = texture.width;
            textureHeight = texture.height;
        }

        // normalize the texRect start point to u,v texture coordinates
        startU = static_cast<float>(texRect.left) / static_cast<float>(textureWidth);
        startV = static_cast<float>(texRect.top) / static_cast<float>(textureHeight);

        textureRectWidth  = static_cast<float>( texRect.right - texRect.left);
        textureRectHeight = static_cast<float>( texRect.bottom - texRect.top );

        // check if we got a zero texRect
        if (textureRectWidth != 0)
            // calcuate the u Width  based on the rect
            widthU = (static_cast<float>( texRect.right - texRect.left) / textureWidth );
        else
            // no texRect was given select all the texture
            widthU = 1;

        // check if we got a zero texRect
        if (textureRectHeight != 0)
            // calcuate the v Width  based on the rect
            heightV = (static_cast<float>( texRect.bottom - texRect.top ) / textureHeight );
        else
            // no texRect was given select all the texture
            heightV = 1;
    }

    int spriteWidth, spriteHeight;
    spriteWidth = spriteRect.right - spriteRect.left;
    spriteHeight = spriteRect.bottom - spriteRect.top;

    startV = 1 - startV;

    Point quadPos = Point(spriteRect.left, spriteRect.top);

    GLuint vIndex = vertices.size();

    vertices.emplace_back(quadPos.x, quadPos.y, 0, tintColor,
                          startU, startV);
    vertices.emplace_back(quadPos.x + spriteWidth * scale.x, quadPos.y, 0,tintColor,
                          startU + widthU, startV);
    vertices.emplace_back(quadPos.x, quadPos.y + spriteHeight * scale.y, 0, tintColor,
                          startU, startV - heightV);
    vertices.emplace_back(quadPos.x + spriteWidth * scale.x,
                          quadPos.y + spriteHeight * scale.y, 0, tintColor,
                          startU + widthU, startV - heightV);
    
    // exceeding MAX_QUADS is very bad and will cause weird graphicals bugs
    // this check here to make sure it is clear when MAX_QUADS was exceeded
    if (vertices.size() > Sprite::MAX_QUADS * 4)
    {
        std::cout << "ARRAY OUT OF BOUNDS\n";
        std::cout << "Array size is " << vertices.size() << "\n";
    }

    // triangle 201
    indices.push_back(vIndex); // #2 vertex  0---1 4---5
    indices.push_back(vIndex + 2);     // #0 vertex  -   - -   -
    indices.push_back(vIndex + 1); // #1 vertex  2---3 6---7
    // triangle 213
    indices.push_back(vIndex + 2); // #2 vertex
    indices.push_back(vIndex + 3); // #1 vertex
    indices.push_back(vIndex + 1); // #3 vertex
}

//-----------------------------------------------------------------------------
// Name : Sprite (constructor)
//-----------------------------------------------------------------------------
Sprite::Sprite()
{
    m_vertexArrayObject = 0;
    m_vertexBuffer = 0;
    m_indicesBuffer = 0;

    m_fScaleWidth = 1;
    m_fScaleHeight = 1;
}

//-----------------------------------------------------------------------------
// Name : Sprite (Destructor)
//-----------------------------------------------------------------------------
Sprite::~Sprite()
{}

//-----------------------------------------------------------------------------
// Name : Init ()
//-----------------------------------------------------------------------------
bool Sprite::Init()
{
    glGenVertexArrays(1, &m_vertexArrayObject);
    glBindVertexArray(m_vertexArrayObject);
    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexSprite) * MAX_QUADS * 4, NULL, GL_DYNAMIC_DRAW);
    glGenBuffers(1, &m_indicesBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indicesBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(VertexIndex) * MAX_QUADS * 6, NULL, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(VertexSprite), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexSprite), (GLvoid*)offsetof(VertexSprite, diffuse));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexSprite), (GLvoid*)offsetof(VertexSprite, uv));

    glBindVertexArray(0);

    return true;
}

//-----------------------------------------------------------------------------
// Name : AddTintedQuad ()
//-----------------------------------------------------------------------------
bool Sprite::AddTintedQuad(const Rect &spriteRect, const glm::vec4 &tintColor)
{
    return AddQuad(spriteRect, tintColor, Texture(NO_TEXTURE, 0, 0), EMPTY_RECT, Point(m_fScaleWidth, m_fScaleHeight));
}

//-----------------------------------------------------------------------------
// Name : AddTexturedQuad ()
//-----------------------------------------------------------------------------
bool Sprite::AddTexturedQuad(const Rect& spriteRect, const Texture& texture, const Rect& texRect)
{
    return AddQuad(spriteRect, WHITE_COLOR, texture, std::move(texRect), Point(m_fScaleWidth, m_fScaleHeight));
}

//-----------------------------------------------------------------------------
// Name : AddTintedTexturedQuad ()
//-----------------------------------------------------------------------------
bool Sprite::AddTintedTexturedQuad(const Rect &spriteRect, glm::vec4 tintColor, const Texture& texture, const Rect &texRect/* = Rect(0, 0, 0, 0)*/)
{
    return AddQuad(spriteRect, tintColor, texture, texRect, Point(m_fScaleWidth, m_fScaleHeight));
}

//-----------------------------------------------------------------------------
// Name : AddQuad ()
//-----------------------------------------------------------------------------
bool Sprite::AddQuad(const Rect& spriteRect, glm::vec4 tintColor, const Texture& texture, const Rect& texRect,Point scale = Point(1,1))
{
    if (m_vertexStreams.size() == 0 || texture.name != m_vertexStreams[m_vertexStreams.size() - 1].texture.name)
        m_vertexStreams.emplace_back(texture);

    m_vertexStreams[m_vertexStreams.size() - 1].addQuad(spriteRect, texRect, tintColor, scale);

    return true;
}

//-----------------------------------------------------------------------------
// Name : Render ()
//-----------------------------------------------------------------------------
bool Sprite::Render(Shader* shader)
{
    shader->Use();

    for (StreamOfVertices& vertexStream : m_vertexStreams)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
         glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(VertexSprite) * vertexStream.vertices.size(),
                         vertexStream.vertices.data());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indicesBuffer);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(VertexIndex) * vertexStream.indices.size(),
                        vertexStream.indices.data());

        if (vertexStream.texture.name != 0)
        {
             glUniform1i( glGetUniformLocation(shader->Program, "textured"), 1);
             glBindTexture(GL_TEXTURE_2D, vertexStream.texture.name);
        }
        else
            glUniform1i( glGetUniformLocation(shader->Program, "textured"), 0);

        glBindVertexArray(m_vertexArrayObject);
        glDrawElements(GL_TRIANGLES, vertexStream.indices.size() , GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
    }

    return true;
}

//-----------------------------------------------------------------------------
// Name : Render ()
//-----------------------------------------------------------------------------
void Sprite::Clear()
{
    m_vertexStreams.clear();
    m_fScaleWidth  = 1;
    m_fScaleHeight = 1;
}
