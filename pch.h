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

#ifndef  _PCH_H
#define  _PCH_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <utility>
#include <functional>
#include <future>

#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL // needed for gtx extensions
#include <glm/gtx/intersect.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include<png.h>
#include<jpeglib.h>

#ifdef FBX
    #include <fbxsdk.h>
#endif

#ifdef _WIN32
    #include <windows.h>
    #undef max
    #undef min
#else
    #include <sys/time.h>
    
    #include <X11/Xlib.h>
    #include <X11/Xutil.h>
    #include <X11/extensions/Xrandr.h>
    #include <GL/glx.h>
    
    #include <wayland-client.h>
    #include <wayland-client-protocol.h>
    #include <wayland-egl.h>
    #include <wayland-cursor.h>
    #include <wayland-server.h>
    #include <xdg-shell-unstable-v6-protocol.h>
    #include <xkbcommon/xkbcommon.h>
    
    #include <EGL/egl.h>
    #include <EGL/eglext.h>
#endif

#include <cinttypes>
#include <cassert>
#include <cstring>

#include <boost/signals2/signal.hpp>
#include <boost/signals2.hpp>
#include <boost/bind/bind.hpp>

#include<cstdio>

#endif  //_PCH_H
