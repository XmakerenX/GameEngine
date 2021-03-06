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

#include "subMesh.h"
#include <glm/ext/scalar_constants.hpp>

struct OBJnode
{
    GLuint index;
    GLboolean averaged;
    OBJnode * next;
};

//-----------------------------------------------------------------------------
// Name : SubMesh (constructor)
//-----------------------------------------------------------------------------
// TODO: make vertices and indices movable to reduce overhead
SubMesh::SubMesh(const std::vector<Vertex>& vertices, const std::vector<VertexIndex>& indices)
{
    this->m_vertices = vertices;
    this->m_indices = indices;

    this->m_VAO = 0;
    this->m_VBO = 0;
    this->m_EBO = 0;

    // Now that we have all the required data, set the vertex buffers and its attribute pointers.
    this->setupMesh();
}

//-----------------------------------------------------------------------------
// Name : SubMesh (copy constructor)
//-----------------------------------------------------------------------------
SubMesh::SubMesh(const SubMesh& copySubMesh)
    :m_vertices(copySubMesh.m_vertices), m_indices(copySubMesh.m_indices)
{
    m_VAO = 0;
    m_VBO = 0;
    m_EBO = 0;
    setupMesh();
}

//-----------------------------------------------------------------------------
// Name : SubMesh (copy assignment)
//-----------------------------------------------------------------------------
SubMesh& SubMesh::operator=(const SubMesh& copy)
{
    m_vertices = copy.m_vertices;
    m_indices = copy.m_indices;
    
    m_VAO = 0;
    m_VBO = 0;
    m_EBO = 0;
    setupMesh();
    
    return *this;
}

//-----------------------------------------------------------------------------
// Name : SubMesh (move constructor)
//-----------------------------------------------------------------------------
SubMesh::SubMesh(SubMesh&& moveSubMesh)
    :m_vertices(std::move(moveSubMesh.m_vertices)), m_indices(std::move(moveSubMesh.m_indices))
{
    m_VAO = moveSubMesh.m_VAO;
    m_VBO = moveSubMesh.m_VBO;
    m_EBO = moveSubMesh.m_EBO;
    
    moveSubMesh.m_VAO = 0;
    moveSubMesh.m_VBO = 0;
    moveSubMesh.m_EBO = 0;
}

//-----------------------------------------------------------------------------
// Name : SubMesh (move assignment)
//-----------------------------------------------------------------------------
SubMesh& SubMesh::operator=(SubMesh&& move)
{
    m_vertices = std::move(move.m_vertices);
    m_indices = std::move(move.m_indices);
    
    m_VAO = move.m_VAO;
    m_VBO = move.m_VBO;
    m_EBO = move.m_EBO;
    
    move.m_VAO = 0;
    move.m_VBO = 0;
    move.m_EBO = 0;
    
    return *this;
}

//-----------------------------------------------------------------------------
// Name : SubMesh (destructor)
//-----------------------------------------------------------------------------
SubMesh::~SubMesh()
{
    if (m_EBO != 0)
        glDeleteBuffers(1, &m_EBO);
    
    if (m_VBO != 0)
        glDeleteBuffers(1, &m_VBO);
    
    if (m_VAO != 0)
        glDeleteVertexArrays(1, &m_VAO);
}


//-----------------------------------------------------------------------------
// Name : Draw
//-----------------------------------------------------------------------------
void SubMesh::Draw()
{
    // Draw mesh
    glBindVertexArray(this->m_VAO );
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_EBO );
    glDrawElements(GL_TRIANGLES, this->m_indices.size(), GL_UNSIGNED_INT, 0);
    
    glBindVertexArray(0);
}

//-----------------------------------------------------------------------------
// Name : IntersectTriangle
//-----------------------------------------------------------------------------
bool SubMesh::IntersectTriangle(glm::vec3& rayObjOrigin ,glm::vec3& rayObjDir, int& faceCount)
{
    for (int i = 0; i < m_indices.size(); i += 3)
    {
        glm::vec3& v0 = m_vertices[m_indices[i]].Position;
        glm::vec3& v1 = m_vertices[m_indices[i+1]].Position;
        glm::vec3& v2 = m_vertices[m_indices[i+2]].Position;
        glm::vec2 bray;

        float distance;
        if (glm::intersectRayTriangle(rayObjOrigin, rayObjDir, v0, v1,v2, bray, distance))
        {
            faceCount = i / 3;
            return true;
        }
    }

    // ray didn't intersect with any triangle
    return false;
}

//-----------------------------------------------------------------------------
// Name : CalcVertexNormals
//-----------------------------------------------------------------------------
void SubMesh::CalcVertexNormals(GLfloat angle)
{
    glm::vec3 u,v;

    std::vector<glm::vec3> facenorms;
    //GLuint   numfacetnorms;       /* number of facetnorms in model */
    //GLfloat* facetnorms;          /* array of facetnorms */

    glm::vec3 average;
    GLuint avg;

    OBJnode** members;
    OBJnode* node;
    GLfloat dot, cos_angle;

    for (int i = 0; i < m_indices.size(); i += 3)
    {
        glm::vec3 faceNorm;

        u.x = m_vertices[m_indices[i + 1]].Position.x -
                m_vertices[m_indices[i + 0]].Position.x;
        u.y = m_vertices[m_indices[i + 1]].Position.y -
                m_vertices[m_indices[i + 0]].Position.y;
        u.z = m_vertices[m_indices[i + 1]].Position.z -
                m_vertices[m_indices[i + 0]].Position.z;

        v.x = m_vertices[m_indices[i + 2]].Position.x -
                m_vertices[m_indices[i + 0]].Position.x;
        v.y = m_vertices[m_indices[i + 2]].Position.y -
                m_vertices[m_indices[i + 0]].Position.y;
        v.z = m_vertices[m_indices[i + 2]].Position.z -
                m_vertices[m_indices[i + 0]].Position.z;

        faceNorm = glm::cross(u,v);
        faceNorm = glm::normalize(faceNorm);
        facenorms.push_back(std::move(faceNorm));
    }

    // calculate the cosine of the angle (in degrees)
    cos_angle = std::cos(angle * glm::pi<float>() / 180.0);

    // allocate a structure that will hold a linked list of triangle indices for each vertex
    members = new OBJnode*[m_vertices.size() + 1];
    for (int i = 0; i <= m_vertices.size(); i++)
        members[i] = nullptr;

    for (int i = 0; i < m_indices.size(); i += 3)
    {
       node = new OBJnode();
       node->index = i;
       node->next = members[m_indices[i]];
       members[m_indices[i]] = node;

       node = new OBJnode();
       node->index = i;
       node->next = members[m_indices[i + 1]];
       members[m_indices[i + 1]] = node;

       node = new OBJnode();
       node->index = i;
       node->next = members[m_indices[i + 2]];
       members[m_indices[i + 2]] = node;
    }

    for (int vIndex = 0; vIndex < m_vertices.size(); vIndex++)
    {
        node = members[vIndex];
        if (!node)
            std::cerr << "CalcVertexNormals(): vertex without a triangle\n";

        average.x = 0; average.y = 0; average.z = 0;
        avg = 0;
        while (node)
        {
            dot = glm::dot(facenorms[node->index], facenorms[members[vIndex]->index]);
            if (dot > cos_angle)
            {
                node->averaged = GL_TRUE;
                average.x += facenorms[node->index].x;
                average.y += facenorms[node->index].y;
                average.z += facenorms[node->index].z;
                avg = 1; // we averaged at least one normal
            }
            else
                node->averaged = GL_FALSE;

            node = node->next;
        }

        if (avg)
        {
            average = glm::normalize(average);
            m_vertices[vIndex].Normal = average;
        }

    }

    for (int i = 0; i < m_vertices.size(); i++)
    {
        OBJnode* tail;
        node = members[i];
        while (node)
        {
            tail = node;
            node = node->next;
            delete tail;
        }
    }
    delete[] members;

    //setupMesh();

}

//-----------------------------------------------------------------------------
// Name : setupMesh
//-----------------------------------------------------------------------------
void SubMesh::setupMesh()
{
    // Create buffers/arrays
    if (this->m_VAO == 0)
        glGenVertexArrays(1, &this->m_VAO );

    if (this->m_VBO == 0)
        glGenBuffers(1, &this->m_VBO );

    if (this->m_EBO == 0)
        glGenBuffers(1, &this->m_EBO );

    glBindVertexArray(this->m_VAO );
    // Load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO );
    // A great thing about structs is that their memory layout is sequential for all its items.
    // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
    // again translates to 3/2 floats which translates to a byte array.
    glBufferData(GL_ARRAY_BUFFER, this->m_vertices.size() * sizeof(Vertex), this->m_vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_EBO );
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->m_indices.size() * sizeof(VertexIndex), this->m_indices.data(), GL_STATIC_DRAW);

    // Set the vertex attribute pointers
    // Vertex Positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Vertex Normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
    glEnableVertexAttribArray(1);
    // Vertex Texture Coords
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}
