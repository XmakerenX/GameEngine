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

#ifndef  _OBJLOADER_H
#define  _OBJLOADER_H

#include <unordered_map>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "../Render/RenderTypes.h"
// for vertex
#include "../Render/Mesh.h"
#include "AssetManager.h"


class AssetManager;
struct Model;

struct Group
{
    Group(std::string& rName);

    GLushort addVertex(glm::vec3 pos, glm::vec3 normal, glm::vec2 texCords);
    GLushort addVertex(Model& model,int* v, int* t, int* n);

    std::string name;
    GLuint numTrinagles;

    std::vector<Vertex> vertices;
    std::vector<VertexIndex> indices;

    GLuint material;
};

struct Model
{
    Model(std::string newMeshPath);
    ~Model();

    Group& addGroup(std::string name);

    std::string meshPath;
    std::string matrialPath;

    GLuint numVertices;
    GLfloat* verticesPos;

    GLuint numNormals;
    GLfloat* normals;

    GLuint numTexCords;
    GLfloat* texCords;

    GLuint numfaceNormals;
    GLfloat* faceNormals;

    GLuint numTrinagles;
    GLuint numMaterials;
    GLuint numGroups;
    
    std::vector<Group> groups;
    std::unordered_map<std::string,GLuint> materials;

    glm::vec3 pos;
};

void objFirstPass(AssetManager &asset, std::ifstream& in , Model& model);
void objSecondPass(std::ifstream& in ,Model& model);
void objReadMatrial(AssetManager& asset, Model& model, std::string matrialPath);

#endif // _OBJLOADER_H
