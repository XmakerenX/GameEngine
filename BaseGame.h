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

#ifndef  _BaseGame_H
#define  _BaseGame_H

#include "AssetLoading/AssetManager.h"

#include <iostream>
#include <sstream>

#include <GL/gl.h>
#include <GL/glew.h>

#include "timer.h"
#include "GameWindow/BaseWindow.h"
#include "Render/Scene.h"
#include "Input/input.h"
#include "Render/Sprite.h"

class BaseGame
{
public:
    BaseGame();
    virtual ~BaseGame();

    bool initGame(BaseWindow* window,int width, int height);

    void setRenderStates();

    void drawing();
    void renderFPS(Sprite& textSprite, mkFont& font);

    void reshape(int width, int height);
    void ProcessInput(double timeDelta, bool keyStatus[256], float X, float Y);

    int  BeginGame();
    bool Shutdown();

protected:    
    virtual void initGUI() {};
    virtual void renderGUI() {};
    virtual bool handleMouseEvent(MouseEvent event, const ModifierKeysStates &modifierStates);
    virtual void sendKeyEvent(unsigned char key, bool down) {};
    virtual void sendVirtualKeyEvent(GK_VirtualKey virtualKey, bool down, const ModifierKeysStates& modifierStates) {};
    virtual void sendMouseEvent(MouseEvent event, const ModifierKeysStates &modifierStates);
    virtual void onSizeChanged() {};

    BaseWindow* m_window;
    bool m_gameRunning;

    Timer m_timer;

    Scene* m_scene;
    bool m_sceneInput;

    bool m_keysStatus[256];
    Point m_oldCursorLoc;
    bool m_mouseDrag;

    AssetManager m_asset;
    mkFont* m_font;
    Sprite m_sprites[2];
    Sprite m_topSprites[2];

    Shader* m_spriteShader;
    Shader* m_spriteTextShader;
};

#endif  //_BaseGame_H
