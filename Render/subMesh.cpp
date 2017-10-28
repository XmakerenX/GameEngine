#include "subMesh.h"

struct OBJnode
{
    GLuint index;
    GLboolean averaged;
    OBJnode * next;
};

//-----------------------------------------------------------------------------
// Name : SubMesh (constructor)
//-----------------------------------------------------------------------------
SubMesh::SubMesh(std::vector<Vertex> vertices, std::vector<GLushort> indices)
{
    this->vertices = vertices;
    this->indices = indices;

    // Now that we have all the required data, set the vertex buffers and its attribute pointers.
    this->setupMesh();
}

//-----------------------------------------------------------------------------
// Name : Draw
//-----------------------------------------------------------------------------
void SubMesh::Draw()
{
    // Draw mesh
    glBindVertexArray(this->VAO);
    //glDrawElements(GL_TRIANGLE_STRIP, this->indices.size(), GL_UNSIGNED_SHORT, 0);
    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_SHORT, 0);

    glBindVertexArray(0);

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

    for (int i = 0; i < indices.size(); i += 3)
    {
        glm::vec3 faceNorm;

        u.x = vertices[indices[i + 1]].Position.x -
                vertices[indices[i + 0]].Position.x;
        u.y = vertices[indices[i + 1]].Position.y -
                vertices[indices[i + 0]].Position.y;
        u.z = vertices[indices[i + 1]].Position.z -
                vertices[indices[i + 0]].Position.z;

        v.x = vertices[indices[i + 2]].Position.x -
                vertices[indices[i + 0]].Position.x;
        v.y = vertices[indices[i + 2]].Position.y -
                vertices[indices[i + 0]].Position.y;
        v.z = vertices[indices[i + 2]].Position.z -
                vertices[indices[i + 0]].Position.z;

        faceNorm = glm::cross(u,v);
        faceNorm = glm::normalize(faceNorm);
        facenorms.push_back(std::move(faceNorm));
    }

    // calculate the cosine of the angle (in degrees)
    cos_angle = std::cos(angle * M_PI / 180.0);

    // allocate a structure that will hold a linked list of triangle indices for each vertex
    members = new OBJnode*[vertices.size() + 1];
    for (int i = 0; i <= vertices.size(); i++)
        members[i] = nullptr;

    for (int i = 0; i < indices.size(); i += 3)
    {
       node = new OBJnode();
       node->index = i;
       node->next = members[indices[i]];
       members[indices[i]] = node;

       node = new OBJnode();
       node->index = i;
       node->next = members[indices[i + 1]];
       members[indices[i + 1]] = node;

       node = new OBJnode();
       node->index = i;
       node->next = members[indices[i + 2]];
       members[indices[i + 2]] = node;
    }

    for (int vIndex = 0; vIndex < vertices.size(); vIndex++)
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
            vertices[vIndex].Normal = average;
        }

    }

    for (int i = 0; i < vertices.size(); i++)
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

}

//-----------------------------------------------------------------------------
// Name : setupMesh
//-----------------------------------------------------------------------------
void SubMesh::setupMesh()
{
    // Create buffers/arrays
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);

    glBindVertexArray(this->VAO);
    // Load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    // A great thing about structs is that their memory layout is sequential for all its items.
    // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
    // again translates to 3/2 floats which translates to a byte array.
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), this->vertices.data(), GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLushort), this->indices.data(), GL_STATIC_DRAW);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);

    // Set the vertex attribute pointers
    // Vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
    // Vertex Normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
    // Vertex Texture Coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);
}