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

#ifndef  _FREECAM_H
#define  _FREECAM_H

#include "Camera.h"

class FreeCam : public Camera
{
public:
    struct RotationLimits
    {
        int minX;
        int maxX;
        int minZ;
        int maxZ;
    };

    //-----------------------------------------------------------------------------
    // Constructors & Destructors
    //-----------------------------------------------------------------------------
    FreeCam();
    FreeCam(const Camera* pCamera);

    //-----------------------------------------------------------------------------
    // Public Functions for This Class.
    //-----------------------------------------------------------------------------
    CAMERA_MODE GetCameraMode() const { return MODE_FREE;}
    void        Rotate       (float x, float y, float z);
    void        RotateAroundPoint(glm::vec3& point, float xDistance, float yDistance,
                                  RotationLimits rotLimits);
    void        SetCameraDetails(const Camera* pCamera);
    void        Move(GLuint direction, float distance);
    void        Yaw(float angle);
    void        Pitch(float angle);
    glm::mat4x4 &getRotateMatrix();

private:
    glm::vec3 m_rightAxis;
    glm::mat4x4 m_rotateMatrix;
};

#endif  //_FREECAM_H
