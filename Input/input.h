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

#ifndef  _INPUT_H
#define  _INPUT_H

#include "virtualKeysGame.h"

struct ModifierKeysStates
{
    ModifierKeysStates(bool shiftState, bool ctrlState, bool altState)
    {
        bShift = shiftState;
        bCtrl = ctrlState;
        bAlt = altState;
    }

    bool bShift;
    bool bCtrl;
    bool bAlt;
};

//Keys scancodes
#define GK_UP    103
#define GK_DOWN  108
#define GK_LEFT  105
#define GK_RIGHT 106

#define GK_A 30
#define GK_S 31
#define GK_D 32
#define GK_W 17

#define GK_Z 44
#define GK_X 45

#define GK_Q 16
#define GK_E 18

#define GK_SPACE 27 

#endif  //_INPUT_H
