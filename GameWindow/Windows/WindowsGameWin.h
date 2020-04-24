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

#ifndef  _WINDOWSGAMEWIN_H
#define  _WINDOWSGAMEWIN_H

#include <windows.h>
#undef min
#undef max
#include "../BaseWindow.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

typedef BOOL(WINAPI *wglChoosePixelFormatARBProc)(HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats);
typedef HGLRC(WINAPI *wglCreateContextAttribsARBProc)(HDC hDC, HGLRC hshareContext, const int *attribList);
#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092

#define WGL_DRAW_TO_WINDOW_ARB 0x2001
#define WGL_SUPPORT_OPENGL_ARB 0x2010
#define WGL_DOUBLE_BUFFER_ARB 0x2011
#define WGL_PIXEL_TYPE_ARB 0x2013
#define WGL_COLOR_BITS_ARB 0x2014
#define WGL_DEPTH_BITS_ARB 0x2022
#define WGL_STENCIL_BITS_ARB 0x2023
#define WGL_TYPE_RGBA_ARB 0x202B

#define WGL_SAMPLE_BUFFERS_ARB 0x2041
#define WGL_SAMPLES_ARB 0x2042

struct MonitorInfo
{
    struct Mode
    {
        Mode(DEVMODE _deviceMode ,GLuint _width, GLuint _height, GLuint _frequency)
        :width(_width), height(_height), frequency(_frequency)
        {
            deviceMode = _deviceMode;
        }

        DEVMODE deviceMode;
        GLuint width;
        GLuint height;
        GLuint frequency;
    };
    
    MonitorInfo(int _index , const std::string& _deviceName,const Rect& _positionRect, const std::vector<Mode>& _modes)
    :deviceName(_deviceName),modes(_modes)
    {
        index = _index;
        positionRect = _positionRect;
    }
    
    MonitorInfo(int _index , const Rect _positionRect, std::vector<Mode>&& _modes)
    :modes(_modes)
    {
        index = _index;
        positionRect = _positionRect;
    }
    
    int index;
    std::string deviceName;
    Rect positionRect;
    std::vector<Mode> modes;
};

class WindowsGameWin : public BaseWindow
{
public:
    WindowsGameWin();
    virtual ~WindowsGameWin();
    void setHINSTANCE(HINSTANCE hInstance);
    
    void pumpMessages   ();
    bool closeWindow    ();

    void setFullScreenMode(bool fullscreen);
    bool setMonitorResolution(int monitorIndex, Resolution newResolution);
    void setWindowPosition(int x, int y);
    void setWindowSize(GLuint width, GLuint height);
    void moveWindowToMonitor(int monitorIndex);

    void setCursorPos(Point newPos);
    Point getCursorPos();

    Point getWindowPosition();
    GLuint getWindowCurrentMonitor();
    
    void copyToClipboard(const std::string& text);
     std::string PasteClipboard();
    
    std::vector<std::vector<Mode1>> getMonitorsModes() const;
    
    virtual std::function<void (const std::string&)> getCopyToClipboardFunc();
    virtual std::function<std::string (void)> getPasteClipboardFunc();
    
private:    
    LRESULT CALLBACK windowProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
    static LRESULT CALLBACK staticWindowProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
    
    bool platformInit(int width, int height);
    bool createWindow   (int width, int height);
    bool createOpenGLContext();
    
    virtual void glSwapBuffers();
    virtual void getMonitorsInfo();
    
    HINSTANCE m_hInstance;
    HWND m_hWnd;
    HDC	m_hDC;
    HGLRC m_hRC;

    std::vector<MonitorInfo> m_monitors;
    GLuint m_primaryMonitorIndex;
};

#endif  //_WINDOWSGAMEWIN_H
