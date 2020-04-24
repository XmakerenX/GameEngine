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

#include "TestingGame.h" 
#include <Render/GUI/DialogUI.cpp>

TestingGame::TestingGame()
{
    m_scene = new Scene();
}

void TestingGame::initGUI()
{
    m_testDialog.init(500, 735, 18, "Edit Dialog", "", glm::vec4(1.0f, 1.0f, 1.0f, 0.0f), m_asset);
    m_testDialog.setClipboardFunctions(m_window->getCopyToClipboardFunc(), m_window->getPasteClipboardFunc());
    
    //void setClipboardFunctions(std::function<void (std::string)> clipboardCopyFunc, std::function<std::string (void)> clipboardPasteFunc);
    
    m_testDialog.setLocation(50, 50);
    m_testDialog.initDefControlElements(m_asset);
//     ListBoxUI<int>* listbox;
//     m_testDialog.addListBox(5, 0, 0, 200, 75, false ,&listbox);
//     listbox->AddItem("0", 0);
//     listbox->AddItem("1", 0);
//     listbox->AddItem("2", 0);
    
//     m_testDialog.addButton(5, "Button", 0, 0, 200 , 25 , 0);
//     m_testDialog.addButton(6, "Button2", 0, 25, 200 , 25 , 0);
//     m_testDialog.addButton(7, "Button3", 0, 50, 200 , 25 , 0);
    ComboBoxUI<int>* pCombo;
    m_testDialog.addComboBox(5, "", 0, 75, 200, 25, 0, &pCombo);
    pCombo->AddItem("0", 0);
    pCombo->AddItem("1", 0);
    pCombo->AddItem("2", 0);
    
    
}

void TestingGame::renderGUI()
{
    m_testDialog.OnRender(m_sprites, m_topSprites, m_asset, m_timer.getCurrentTime());
}

void TestingGame::sendKeyEvent(unsigned char key, bool down)
{
    m_testDialog.handleKeyEvent(key, down);
}

void TestingGame::sendVirtualKeyEvent(GK_VirtualKey virtualKey, bool down, const ModifierKeysStates& modifierStates)
{
    m_testDialog.handleVirtualKeyEvent(virtualKey, down, modifierStates);
}

void TestingGame::sendMouseEvent(MouseEvent event, const ModifierKeysStates &modifierStates)
{
    BaseGame::sendMouseEvent(event, modifierStates);
    m_testDialog.handleMouseEvent(event, modifierStates);
}
