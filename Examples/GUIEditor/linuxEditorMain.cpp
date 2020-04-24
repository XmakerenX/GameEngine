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

#include <iostream>
#include <string>
#include "GUIEditor.h"
#include <GameWindow/Linux/LinuxX11Window.h>

int main(int argc, char* argv[])
{
    GUIEditor gamewin;
    BaseWindow* window = new LinuxX11Window();
    std::string fontName = "NotoMono";
    std::string path;

    std::cout << "--------------------------------\n";
    std::cout << "starting init window\n";
    std::cout << "--------------------------------\n";

    std::cout << "starting init OpenGL\n";
    if (!gamewin.initGame(window, 1024, 768))
    {
        std::cout << "Error occured, Quiting..\n";
        return 1;
    }

    std::cout << "--------------------------------\n";
    std::cout << "Beginning game\n";
    int retCode = gamewin.BeginGame();

    if (!gamewin.Shutdown())
        return 1;

    return retCode;
}

