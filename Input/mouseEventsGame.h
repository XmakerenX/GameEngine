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

#ifndef  _MOUSEEVENTSGAME_H
#define  _MOUSEEVENTSGAME_H

#include "../Render/RenderTypes.h"

enum class MouseEventType{Unknown = 0,
                          LeftButton,
                          DoubleLeftButton,
                          MiddleButton,
                          DoubleMiddleButton,
                          RightButton,
                          DoubleRightButton,
                          ScrollHoriz,
                          ScrollVert,
                          MouseMoved};

class MouseEvent
{
public:

    MouseEvent() : cursorPos(0,0)
    {
        type = MouseEventType::Unknown;
        down = false;
        timeStamp = 0;
        nLinesToScroll = 0;
    }

    MouseEvent(MouseEventType newType, Point newCursorPos, bool newDown, double newTimeStamp, int newLinesToScroll)
        :cursorPos(newCursorPos)
    {
        type = newType;
        down = newDown;
        timeStamp = newTimeStamp;
        nLinesToScroll = newLinesToScroll;
    }

    MouseEventType type;
    Point cursorPos;
    bool down;
    double timeStamp;
    int nLinesToScroll;

};

#endif  //_MOUSEEVENTSGAME_H
