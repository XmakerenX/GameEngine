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

#include "GUIEditor.h" 

GUIEditor::GUIEditor()
{}

void GUIEditor::initGUI()
{
    m_editDialog.SetWindow(m_window);
    m_editDialog.init(500, 735, 18, "Edit Dialog", "", glm::vec4(1.0f, 1.0f, 1.0f, 0.0f), this->m_asset);
    m_editDialog.setClipboardFunctions(m_window->getCopyToClipboardFunc(), m_window->getPasteClipboardFunc());
    m_editDialog.setLocation(550, 0);
    m_editDialog.initDefControlElements(this->m_asset);
    m_editDialog.CreateDialogUI(this->m_asset);
}

void GUIEditor::renderGUI()
{
    m_editDialog.OnRender(this->m_sprites, this->m_topSprites, this->m_asset, this->m_timer.getCurrentTime());
}

void GUIEditor::sendKeyEvent(unsigned char key, bool down)
{
    m_editDialog.handleKeyEvent(key, down);
}

void GUIEditor::sendVirtualKeyEvent(GK_VirtualKey virtualKey, bool down, const ModifierKeysStates& modifierStates)
{
    m_editDialog.handleVirtualKeyEvent(virtualKey, down, modifierStates);
}

void GUIEditor::sendMouseEvent(MouseEvent event, const ModifierKeysStates &modifierStates)
{
    BaseGame::sendMouseEvent(event, modifierStates);
    m_editDialog.handleMouseEvent(event, modifierStates);
}
