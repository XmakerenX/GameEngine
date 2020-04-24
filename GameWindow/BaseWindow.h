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

#ifndef  _BaseWindowN_H
#define  _BaseWindowN_H

#include "../AssetLoading/AssetManager.h"
#include <boost/signals2/signal.hpp>

#include <iostream>
#include <sstream>
#include <functional>

#include <GL/gl.h>
#include <GL/glew.h>

#include "../timer.h"
#include "../Render/Scene.h"
#include "../Input/input.h"
#include "../Render/Sprite.h"
#include <boost/signals2.hpp>
#include <boost/signals2.hpp>
#include <boost/signals2.hpp>

struct Resolution
{
    Resolution(GLuint _width, GLuint _height)
        :width(_width), height(_height)
    {}

    GLuint width;
    GLuint height;
};

std::ostream& operator<<(std::ostream& os, const Resolution res);
std::istream& operator>>(std::istream& is, Resolution res);

struct Mode1
{
    Mode1(GLuint _width, GLuint _height)
        :width(_width), height(_height)
    {}

    GLuint width;
    GLuint height;
};

struct MouseDrift
{
    MouseDrift(float _x, float _y)
        :x(_x), y(_y) {}
        
    float x;
    float y;
};

class BaseWindow
{
public:
    typedef boost::signals2::signal<void (int, int)> sizeChangedSignal;
    
    typedef boost::signals2::signal<void (unsigned char , bool)> KeySignal;
    typedef boost::signals2::signal<void (GK_VirtualKey, bool, const ModifierKeysStates&)> VirtualKeySignal;
    typedef boost::signals2::signal<void (MouseEvent, const ModifierKeysStates&)> MouseSignal;
    
    BaseWindow();
    virtual ~BaseWindow();

    virtual bool platformInit(int width, int height) = 0;
    virtual void glSwapBuffers() = 0;
    
    void reshape(int width, int height);
    
    virtual void pumpMessages() = 0;
    virtual bool closeWindow() = 0;

    MouseDrift processInput();
    
    virtual void setFullScreenMode(bool fullscreen) = 0;
    virtual bool setMonitorResolution(int monitorIndex, Resolution newResolution) = 0;
    virtual void setWindowPosition(int x, int y) = 0;
    virtual void moveWindowToMonitor(int monitorIndex) = 0;

    virtual Point getCursorPos() = 0;
    virtual void setCursorPos(Point newPos) = 0;

    virtual Point getWindowPosition() = 0;
    virtual void  getMonitorsInfo() = 0;
    virtual GLuint getWindowCurrentMonitor() = 0;

    virtual std::vector<std::vector<Mode1>> getMonitorsModes() const = 0;

    virtual void copyToClipboard(const std::string& text) = 0;
    virtual std::string PasteClipboard() = 0;
    
    void connectToSizeChangedEvent(const sizeChangedSignal::slot_type& subscriber);
    void connectToKeyEvent(const KeySignal::slot_type& subscriber);
    void connectToVritaulKeyEvent(const VirtualKeySignal::slot_type& subscriber);
    void connectToMouseEvent(const MouseSignal::slot_type& subscriber);
    
    void setTimer(Timer* timer);
    GLuint getWidth();
    GLuint getHeight();
    bool* getKeyStatus();
    virtual std::function<void (const std::string&)> getCopyToClipboardFunc() = 0;
    virtual std::function<std::string (void)> getPasteClipboardFunc() = 0;
    bool isRunning();
    
protected:

    KeySignal sendKeyEvent;
    VirtualKeySignal sendVirtualKeyEvent;
    MouseSignal sendMouseEvent;
    sizeChangedSignal sizeChanged;

    Timer* m_timer;
    GLuint m_winWidth;
    GLuint m_winHeight;
    bool m_running;
    bool m_fullscreen;

    bool m_keysStatus[256];
    Point m_oldCursorLoc;
    bool m_mouseDrag;
};

#endif  //_BaseWindowN_H

