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

#ifndef  _MESHGENERATOR_H
#define  _MESHGENERATOR_H

#include "AssetManager.h"
#include "../Render/Mesh.h"

class MeshGenerator
{
public:
    static Mesh createBoardMesh(AssetManager& assetManager, const glm::vec2& scale);
    static Mesh createSquareMesh(AssetManager& assetManager, const glm::vec2& scale);
    static Mesh createSkyBoxMesh();
    static Mesh createCubeMesh();
    
private:
    static void createBoardSubMeshes(float stepX, float stepZ, std::vector<SubMesh>& boardSubMeshes);
    static void createBoardIndices(std::vector<VertexIndex>& squareIndices, VertexIndex curIndex, int nVertX);
    
    static void createFrameSubMeshes(float stepX, float stepZ, std::vector<SubMesh>& boardSubMeshes);
    static void createHorizontalFrameSquare(std::vector<Vertex>& frameSquaresVertices, std::vector<VertexIndex>& frameIndices, const glm::vec3& framePos, float stepX, float stepZ, int i);
    static void createVerticalFrameSquare(std::vector<Vertex>& frameSquaresVertices, std::vector<VertexIndex>& frameIndices, const glm::vec3& framePos, float stepX, float stepZ, int i);
    static void createCornersFrameSquare(std::vector<Vertex>& frameSquaresVertices, std::vector<VertexIndex>& frameIndices, const glm::vec3& framePos, float stepX, float stepZ);
    static void createFrameSquare(glm::vec3 pos, float stepX, float stepZ, const glm::vec2 uvValues[4],int startValue,std::vector<Vertex>& frameSquaresVertices, std::vector<VertexIndex>& frameIndices);
    static void createSquareIndices(std::vector<VertexIndex>& indices, GLuint vIndex = 0);
    
    static const int nCellHigh = 8;
    static const int nCellWide = 8;
    static const glm::vec2 uvValues[4];
    static const glm::vec2 reverseUvValues[4];
    static const glm::vec2 reverseVerticalUvValues[4];
};

#endif  //_MESHGENERATOR_H
