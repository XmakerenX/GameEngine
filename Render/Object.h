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

#ifndef  _OBJECT_H
#define _OBJECT_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Mesh.h"
#include "../AssetLoading/AssetManager.h"

class Object
{
public:
    Object          (const glm::vec3& pos, const glm::vec3& angle, const glm::vec3& scale, Mesh* pMesh, std::vector<unsigned int> meshAttribute);
    Object          (AssetManager& asset, const glm::vec3& pos, const glm::vec3& angle, const glm::vec3& scale, Mesh* pMesh, std::string shaderPath);
    void InitObject (const glm::vec3& pos, const glm::vec3& angle, const glm::vec3& scale, Mesh* pMesh, std::vector<unsigned int> meshAttribute);
    ~Object         ();

    const glm::mat4x4& GetWorldMatrix          ();
    const glm::mat4x4& GetInverseWorldMatrix   ();
    glm::vec3          GetPosition             ();
    Mesh*              GetMesh                 ();

    bool               IsObjectHidden          ();
    void               SetObjectHidden         (bool newStatus);
    void               SetPos                  (glm::vec3 newPos);
    void               SetRotAngles            (glm::vec3 newRotAngles);
    void               SetScale                (glm::vec3 newScale);

    void               Rotate                  (float x, float y, float z);
    void               TranslatePos            (float x ,float y, float z);
    
    void               AttachMesh              (Mesh* pMesh);
    void               SetObjectAttributes     (std::vector<unsigned int> meshAttribute);
    void               AddObjectAttribute      (unsigned int attribute);
    
    void               Draw                    (Shader* shader, unsigned int attributeIndex, const glm::mat4x4 &matViewProj);
    void               Draw                    (GLuint projectionLoc, GLuint matWorldLoc, GLuint matWorldInverseLoc, unsigned int attributeIndex, const glm::mat4x4& matViewProj);

private:
    void CalculateWorldMatrix();
    glm::vec3   m_pos;
    glm::mat4x4 m_mthxWorld;
    glm::mat4x4 m_mthxInverseWorld;
    glm::mat4x4 m_mtxRot;
    glm::mat4x4 m_mtxScale;
    glm::vec3   m_rotAngles;

    std::vector<unsigned int> m_meshAttributes;
    
    Mesh*       m_pMesh;
    bool        m_hideObject;
    
    bool        m_worldDirty;
};

#endif  //_OBJECT_H
