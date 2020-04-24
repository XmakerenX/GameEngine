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

#ifndef  _MESH_H
#define  _MESH_H

#include <string>
#include "subMesh.h"

class Mesh {

public:
    Mesh();
    Mesh(const std::vector<SubMesh>& sMeshes);
    Mesh(const std::vector<SubMesh>& sMeshes, const std::vector<GLuint>& dMaterials, const std::vector<std::string>& dTextures);
    Mesh(std::vector<SubMesh>&& sMeshes, std::vector<GLuint>&& dMaterials, std::vector<std::string>&& dTextures);
    Mesh(const Mesh& copyMesh);
    Mesh& operator=(const Mesh& copy);
    Mesh(Mesh&& moveMesh);
    Mesh& operator=(Mesh&& move);

    // Render the mesh
    void Draw(unsigned int subMeshIndex);
    void addSubMesh(SubMesh subMesh);

    bool IntersectTriangle(glm::vec3& rayObjOrigin,glm::vec3& rayObjDir, int& faceCount, int& subMeshIndex);
    void CalcVertexNormals(GLfloat angle);

    std::vector<GLuint>& getDefaultMaterials();
    std::vector<std::string>& getDefaultTextures();

private:
    std::vector<SubMesh> m_subMeshes;
    std::vector<GLuint> m_defaultMaterials;
    std::vector<std::string> m_defaultTextures;
};


#endif  //_MESH_H
