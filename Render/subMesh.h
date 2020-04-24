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

#ifndef  _SUBMESH_H
#define  _SUBMESH_H

#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL // needed for gtx extensions
#include <glm/gtx/intersect.hpp>
#include "RenderTypes.h"
#include "Shader.h"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;

    Vertex() :Position(), Normal(), TexCoords() {}
    
    Vertex(glm::vec3 pos, glm::vec3 normal ,glm::vec2 texCord) 
        :Position(pos), Normal(normal), TexCoords(texCord) {}
};

class SubMesh {

public:
    SubMesh(const std::vector<Vertex>& vertices, const std::vector<VertexIndex>& indices);
    SubMesh(const SubMesh& copySubMesh);
    SubMesh& operator=(const SubMesh& copy);
    SubMesh(SubMesh&& moveSubMesh);
    SubMesh& operator=(SubMesh&& move);
    
    ~SubMesh();

    void Draw();

    bool IntersectTriangle(glm::vec3& rayObjOrigin, glm::vec3& rayObjDir, int& faceCount);

    //TODO: cuase this functio to really work
    void CalcVertexNormals(GLfloat angle);

private:
    std::vector<Vertex> m_vertices;
    std::vector<VertexIndex> m_indices;
    
    GLuint m_VAO, m_VBO, m_EBO;

    void setupMesh();
};


#endif  //_SUBMESH_H
