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

#include "BaseWindow.h"

std::ostream& operator<<(std::ostream& os, const Resolution res)
{
    os << res.width << " " << res.height;
    return os;
}

std::istream& operator>>(std::istream& is, Resolution res)
{
    is >> res.width;
    is >> res.height;
    return is;
}

//-----------------------------------------------------------------------------
// Name : BaseWindow (constructor)
//-----------------------------------------------------------------------------
BaseWindow::BaseWindow()
    :m_oldCursorLoc(0,0)
{
    m_running = true;
    m_winWidth = 0;
    m_winHeight = 0;
    m_fullscreen = false;
    m_mouseDrag = false;
    
    for(int i = 0; i < 256; i++)
        m_keysStatus[i] = false;
}

//-----------------------------------------------------------------------------
// Name : BaseWindow (destructor)
//-----------------------------------------------------------------------------
BaseWindow::~BaseWindow(){}

//-----------------------------------------------------------------------------
// Name : reshape
//-----------------------------------------------------------------------------
void BaseWindow::reshape(int width, int height)
{
    std::cout << "reshape called\n";
    std::cout << "New window size is " << width << "X" << height << "\n";
    m_winWidth = width;
    m_winHeight = height;
    sizeChanged(width, height);
}

//-----------------------------------------------------------------------------
// Name : processInput ()
//-----------------------------------------------------------------------------
MouseDrift BaseWindow::processInput()
{
    float X = 0.0f, Y = 0.0f;
    if ( m_mouseDrag )
    {
        Point currentCursorPos = getCursorPos();

        X = (float)(currentCursorPos.x - m_oldCursorLoc.x) / 3.0f;
        Y = (float)(currentCursorPos.y - m_oldCursorLoc.y) / 3.0f;

        setCursorPos( m_oldCursorLoc );
    }
    
    return MouseDrift(X, Y);
}

//-----------------------------------------------------------------------------
// Name : connectToSizeChangedEvent ()
//-----------------------------------------------------------------------------
void BaseWindow::connectToSizeChangedEvent(const sizeChangedSignal::slot_type& subscriber)
{
    sizeChanged.connect(subscriber);
}

//-----------------------------------------------------------------------------
// Name : connectToKeyEvent ()
//-----------------------------------------------------------------------------
void BaseWindow::connectToKeyEvent(const KeySignal::slot_type& subscriber)
{
    sendKeyEvent.connect(subscriber);
}

//-----------------------------------------------------------------------------
// Name : connectToVritaulKeyEvent ()
//-----------------------------------------------------------------------------
void BaseWindow::connectToVritaulKeyEvent(const VirtualKeySignal::slot_type& subscriber)
{
    sendVirtualKeyEvent.connect(subscriber);
}

//-----------------------------------------------------------------------------
// Name : connectToMouseEvent ()
//-----------------------------------------------------------------------------
void BaseWindow::connectToMouseEvent(const MouseSignal::slot_type& subscriber)
{
    sendMouseEvent.connect(subscriber);
}

//-----------------------------------------------------------------------------
// Name : setTimer ()
//-----------------------------------------------------------------------------
void BaseWindow::setTimer(Timer* timer)
{
    m_timer = timer;
}

//-----------------------------------------------------------------------------
// Name : getWidth ()
//-----------------------------------------------------------------------------
GLuint BaseWindow::getWidth()
{
    return m_winWidth;
}

//-----------------------------------------------------------------------------
// Name : getHeight ()
//-----------------------------------------------------------------------------
GLuint BaseWindow::getHeight()
{
    return m_winHeight;
}

//-----------------------------------------------------------------------------
// Name : getHeight ()
//-----------------------------------------------------------------------------
bool* BaseWindow::getKeyStatus()
{
    return m_keysStatus;
}

//-----------------------------------------------------------------------------
// Name : isRunning ()
//-----------------------------------------------------------------------------
bool BaseWindow::isRunning()
{
    return m_running;
}
