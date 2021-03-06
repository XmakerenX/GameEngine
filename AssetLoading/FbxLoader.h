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

#ifndef  _FBXLOADER_H
#define  _FBXLOADER_H

#include <glm/glm.hpp>
#include <fbxsdk.h>
#include <vector>
#include <string>
#include "../Render/subMesh.h"

class FbxLoader
{
public:
    
    FbxLoader()
    {
        m_pFbxSdkManager = nullptr;
    }

    bool LoadMesh(std::string meshPath, std::vector<SubMesh>& subMeshes);
private:
    glm::vec3 readFBXNormal(FbxMesh* mesh, int controlPointIndex, int vertexCounter );
    glm::vec2 readFBXUV(FbxMesh* mesh, int controlPointIndex, int j, int k);

    FbxManager* m_pFbxSdkManager;
};

#endif // _FBXLOADER_H
