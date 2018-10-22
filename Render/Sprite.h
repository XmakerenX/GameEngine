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
