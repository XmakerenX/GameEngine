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

#ifndef  _VIRTUALKEYSGAME_H
#define  _VIRTUALKEYSGAME_H

enum class GK_VirtualKey{GK_UNKNOWN = 0,
                         GK_Escape = 200,
                         GK_SysReq,
                         GK_Pause,
                         GK_Space,
                         GK_BackSpace,
                         GK_Delete, // actully passed as ascii
                         GK_Tab,
                         GK_Linefeed,
                         GK_Return,
                         GK_Home,
                         GK_End,
                         GK_Begin,
                         GK_Left,
                         GK_Up,
                         GK_Right,
                         GK_Down,
                         GK_PageUp,
                         GK_PageDown,
                         GK_Select,
                         GK_Insert,
                         GK_Undo,
                         GK_Redo,
                         GK_Menu,
                         GK_Find,
                         GK_Cancel,
                         GK_Break,
                         GK_F1,
                         GK_F2,
                         GK_F3,
                         GK_F4,
                         GK_F5,
                         GK_F6,
                         GK_F7,
                         GK_F8,
                         GK_F9,
                         GK_F10,
                         GK_F11,
                         GK_F12,
                         GK_KPF1,
                         GK_KPF2,
                         GK_KPF3,
                         GK_KPF4,
                         GK_ShiftL,
                         GK_ShiftR,
                         GK_ControlL,
                         GK_ControlR,
                         GK_MetaL,
                         GK_MetaR,
                         GK_AltL,
                         GK_AltR,
                         GK_SuperL,
                         GK_SuperR,
                         GK_HyperL,
                         GK_HyperR,
                         GK_CapsLock,
                         GK_ShiftLock};

#endif  //_VIRTUALKEYSLINUX_H
