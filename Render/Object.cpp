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

#include "Object.h"

//-----------------------------------------------------------------------------
// Name : Object (constructor)
//-----------------------------------------------------------------------------
Object::Object::Object(const glm::vec3& pos, const glm::vec3& angle, const glm::vec3& scale, Mesh* pMesh, std::vector<unsigned int> meshAttribute) 
    : m_mtxScale(1.0f)
{
    assert(pMesh);
    
    InitObject(pos, angle, scale, pMesh, meshAttribute);
}

//-----------------------------------------------------------------------------
// Name : Object (constructor)
//-----------------------------------------------------------------------------
Object::Object(AssetManager &asset, const glm::vec3 &pos, const glm::vec3 &angle, const glm::vec3 &scale, Mesh *pMesh, std::string shaderPath)
    :m_mtxScale(1.0f)
{
    assert(pMesh);
    
    std::vector<GLuint> meshMaterial = pMesh->getDefaultMaterials();
    std::vector<std::string> meshTextures = pMesh->getDefaultTextures();
    std::vector<unsigned int> objAtteributes;

    if (meshMaterial.size() != 0)
    {
        for (GLuint attributeIndex  = 0; attributeIndex < std::min(meshMaterial.size(), meshTextures.size()); attributeIndex++)
        {
            objAtteributes.push_back(asset.getAttribute(meshTextures[attributeIndex], GL_REPEAT, meshMaterial[attributeIndex], shaderPath));
        }
    }
    else
    {
        Material matt;
        matt.ambient = glm::vec4(0.3f, 0.3f, 0.3f, 1.0);
        matt.diffuse = glm::vec4(0.3f, 0.3f, 0.3f, 1.0);
        matt.emissive = glm::vec4(0.3f, 0.3f, 0.3f, 1.0);
        matt.specular = glm::vec4(0.3f, 0.3f, 0.3f, 1.0);
        matt.power = 1.0f;
        GLuint i = asset.getMaterialIndex(matt);
        objAtteributes.push_back(asset.getAttribute("", GL_REPEAT, i, shaderPath));
    }
    
    InitObject(pos, angle, scale,pMesh,objAtteributes);
}

//-----------------------------------------------------------------------------
// Name : InitObject ()
//-----------------------------------------------------------------------------
void Object::InitObject(const glm::vec3 &pos, const glm::vec3 &angle, const glm::vec3 &scale, Mesh *pMesh, std::vector<unsigned int> meshAttribute)
{
    SetPos(pos);
    SetRotAngles(angle);
    SetScale(scale);
    // update world matrix
    m_worldDirty = true;
    GetWorldMatrix();

    AttachMesh(pMesh);
    SetObjectAttributes(meshAttribute);

    m_hideObject = false;
}

//-----------------------------------------------------------------------------
// Name : Object (destructor)
//-----------------------------------------------------------------------------
Object::~Object()
{

}

//-----------------------------------------------------------------------------
// Name : GetWorldMatrix
//-----------------------------------------------------------------------------
const glm::mat4x4& Object::GetWorldMatrix()
{
    if (m_worldDirty)
    {
        CalculateWorldMatrix();
    }

    return m_mthxWorld;
}

//-----------------------------------------------------------------------------
// Name : GetInverseWorldMatrix
//-----------------------------------------------------------------------------
const glm::mat4x4& Object::GetInverseWorldMatrix()
{
    if (m_worldDirty)
    {
        CalculateWorldMatrix();
    }

    return m_mthxInverseWorld;
}

//-----------------------------------------------------------------------------
// Name : CalculateWorldMatrix
//-----------------------------------------------------------------------------
void Object::CalculateWorldMatrix()
{
    m_mthxWorld = glm::translate(glm::mat4x4(1.0f), m_pos);
    m_mthxWorld = m_mthxWorld * m_mtxScale * m_mtxRot;
    m_mthxInverseWorld = glm::inverse(m_mthxWorld);
    m_worldDirty = false;
}


//-----------------------------------------------------------------------------
// Name : GetPosition
//-----------------------------------------------------------------------------
glm::vec3 Object::GetPosition()
{
    return m_pos;
}

//-----------------------------------------------------------------------------
// Name : GetMesh
//-----------------------------------------------------------------------------
Mesh* Object::GetMesh()
{
    return m_pMesh;
}

//-----------------------------------------------------------------------------
// Name : IsObjectHidden
//-----------------------------------------------------------------------------
bool Object::IsObjectHidden()
{
    return m_hideObject;
}

//-----------------------------------------------------------------------------
// Name : SetObjectHidden
//-----------------------------------------------------------------------------
void Object::SetObjectHidden(bool newStatus)
{
    m_hideObject = newStatus;
}

//-----------------------------------------------------------------------------
// Name : SetPos
//-----------------------------------------------------------------------------
void Object::SetPos(glm::vec3 newPos)
{
    m_pos = newPos;
    m_worldDirty = true;
}

//-----------------------------------------------------------------------------
// Name : SetRotAngles
//-----------------------------------------------------------------------------
void Object::SetRotAngles(glm::vec3 newRotAngles)
{
    glm::mat4x4 mtxRotX(1.0f);
    glm::mat4x4 mtxRotY(1.0f);
    glm::mat4x4 mtxRotZ(1.0f);

    m_rotAngles = newRotAngles;

    mtxRotX = glm::rotate(mtxRotX,m_rotAngles.x,glm::vec3(1.0f,0.0f,0.0f));
    mtxRotY = glm::rotate(mtxRotY,m_rotAngles.y,glm::vec3(0.0f,1.0f,0.0f));
    mtxRotZ = glm::rotate(mtxRotZ,m_rotAngles.z,glm::vec3(0.0f,0.0f,1.0f));
    m_mtxRot = mtxRotX * mtxRotY * mtxRotZ;
    m_worldDirty = true;
}

//-----------------------------------------------------------------------------
// Name : SetObjectScale
//-----------------------------------------------------------------------------
void Object::SetScale(glm::vec3 newScale)
{
	m_mtxScale = glm::scale(m_mtxScale, newScale);
}


//-----------------------------------------------------------------------------
// Name : Rotate
//-----------------------------------------------------------------------------
void Object::Rotate(float x, float y, float z)
{
    glm::mat4x4 mtxRotX(1.0f);
    glm::mat4x4 mtxRotY(1.0f);
    glm::mat4x4 mtxRotZ(1.0f);

    m_rotAngles.x += x;
    m_rotAngles.y += y;
    m_rotAngles.z += z;

    mtxRotX = glm::rotate(mtxRotX,m_rotAngles.x,glm::vec3(1.0f,0.0f,0.0f));
    mtxRotY = glm::rotate(mtxRotY,m_rotAngles.y,glm::vec3(0.0f,1.0f,0.0f));
    mtxRotZ = glm::rotate(mtxRotZ,m_rotAngles.z,glm::vec3(0.0f,0.0f,1.0f));
    m_mtxRot = mtxRotX * mtxRotY * mtxRotZ;
    
    m_worldDirty = true;
}

//-----------------------------------------------------------------------------
// Name : TranslatePos
//-----------------------------------------------------------------------------
void Object::TranslatePos(float x, float y, float z)
{
    if (x != 0 || y != 0 || z != 0)
    {
        m_pos.x += x;
        m_pos.y += y;
        m_pos.z -= z;

        m_worldDirty = true;
    }
}

//-----------------------------------------------------------------------------
// Name : attachMesh
//-----------------------------------------------------------------------------
void Object::AttachMesh(Mesh* pMesh)
{
	m_pMesh = pMesh;
}

//-----------------------------------------------------------------------------
// Name : SetObjectAttributes
//-----------------------------------------------------------------------------
void Object::SetObjectAttributes(std::vector<unsigned int> meshAttribute)
{
	//TODO force moving on the vector paremeter to prevent pointless copying
	m_meshAttributes = meshAttribute;
}

//-----------------------------------------------------------------------------
// Name : AddObjectAttribute
//-----------------------------------------------------------------------------
void Object::AddObjectAttribute(unsigned int attribute)
{
	m_meshAttributes.push_back(attribute);
}

//-----------------------------------------------------------------------------
// Name : Draw
//-----------------------------------------------------------------------------
void Object::Draw(Shader* shader, unsigned int attributeIndex, const glm::mat4x4& matViewProj)
{
    for (unsigned int i = 0; i < m_meshAttributes.size(); ++i)
    {
        if (m_meshAttributes[i] == attributeIndex)
        {
            glm::mat4x4 temp =  matViewProj * GetWorldMatrix();
            glUniformMatrix4fv(glGetUniformLocation(shader->Program, "projection"), 1, GL_FALSE, glm::value_ptr(temp));
            glUniformMatrix4fv(glGetUniformLocation(shader->Program, "matWorld"), 1, GL_FALSE, glm::value_ptr(GetWorldMatrix()));
            glUniformMatrix4fv(glGetUniformLocation(shader->Program, "matWorldInverseT"), 1, GL_FALSE, glm::value_ptr(GetInverseWorldMatrix()));
            m_pMesh->Draw(i);
            break;
        }
    }
}

//-----------------------------------------------------------------------------
// Name : Draw
//-----------------------------------------------------------------------------
void Object::Draw(GLuint projectionLoc, GLuint matWorldLoc, GLuint matWorldInverseLoc, unsigned int attributeIndex, const glm::mat4x4& matViewProj)
{
    for (unsigned int i = 0; i < m_meshAttributes.size(); ++i)
    {
        if (m_meshAttributes[i] == attributeIndex)
        {
            glm::mat4x4 temp =  matViewProj * GetWorldMatrix();
            glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(temp));
            glUniformMatrix4fv(matWorldLoc, 1, GL_FALSE, glm::value_ptr(GetWorldMatrix()));
            //TODO: cache the inverse of worldMatrix as well to reduce overhead
            glUniformMatrix4fv(matWorldInverseLoc, 1, GL_FALSE, glm::value_ptr(GetInverseWorldMatrix()));
            m_pMesh->Draw(i);
            break;
        }
    }
}
