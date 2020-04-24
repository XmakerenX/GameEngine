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

#include "CheckboxUI.h"
#include "DialogUI.h"

//-----------------------------------------------------------------------------
// Name : CheckboxUI (Constructor)
//-----------------------------------------------------------------------------
CheckboxUI::CheckboxUI(DialogUI* pParentDialog, int ID, int x, int y, GLuint width, GLuint height, GLuint nHotkey)
    :ButtonUI(pParentDialog, ID, "", x, y, width, height, nHotkey)
{
    m_type = CHECKBOX;
    m_bChecked = false;
}

//-----------------------------------------------------------------------------
// Name : CheckboxUI (constructor from InputFile)
//-----------------------------------------------------------------------------
CheckboxUI::CheckboxUI(std::istream& inputFile)
    :ButtonUI(inputFile)
{
    m_type = CHECKBOX;

    inputFile >> m_bChecked;
    inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skips to next line
}

//-----------------------------------------------------------------------------
// Name : CCheckboxUI (destructor)
//-----------------------------------------------------------------------------
CheckboxUI::~CheckboxUI(void)
{}

//-----------------------------------------------------------------------------
// Name : Render ()
//-----------------------------------------------------------------------------
void CheckboxUI::Render(Sprite sprites[SPRITES_SIZE], Sprite topSprites[SPRITES_SIZE], double timeStamp)
{
    //no texture was given abort rendering
    if (m_elementsGFX.size() < 2 || m_elementsGFX[BUTTON].texture.name == 0 || m_elementsGFX[MOUSEOVER].texture.name == 0 || !m_bVisible)
        return;

    Point dialogPos = calcPositionOffset();

    //calculate the the button rendering rect
    Rect rcWindow(m_x, m_y, m_x +  m_width, m_y + m_height);

    glm::vec4 tintColor;

    if (!m_bEnabled)
        tintColor = glm::vec4(0.4f, 0.4f, 0.4f, 1.0f);
    else
        if (m_bPressed)
            tintColor = glm::vec4(0.6f, 0.6f,0.6f,1.0f);
        else
            if (m_bMouseOver)
                tintColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
            else
                tintColor = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);

    renderRect(sprites[NORMAL], rcWindow, m_elementsGFX[BUTTON].texture, m_elementsGFX[BUTTON].rcTexture, tintColor, dialogPos);
    if (m_bChecked)
        renderRect(sprites[NORMAL],rcWindow, m_elementsGFX[MOUSEOVER].texture, m_elementsGFX[MOUSEOVER].rcTexture, tintColor, dialogPos);
}

//-----------------------------------------------------------------------------
// Name : handleMouseEvent ()
//-----------------------------------------------------------------------------
bool CheckboxUI::handleMouseEvent(MouseEvent event, const ModifierKeysStates &modifierStates)
{
    if (!m_bEnabled || !m_bVisible)
        return false;

    switch (event.type)
    {
    case MouseEventType::LeftButton:
    case MouseEventType::DoubleLeftButton:
    {
        if (event.down)
        {
            if ( Pressed(event.cursorPos, modifierStates, event.timeStamp) )
                return true;
        }
        else
        {
            if (Released(event.cursorPos))
                    return true;
        }
    }break;
    
    default:
        return false;
    
    }

    return false;
}

//-----------------------------------------------------------------------------
// Name : Pressed ()
//-----------------------------------------------------------------------------
bool CheckboxUI::Pressed(Point pt, const ModifierKeysStates &modifierStates, double timeStamp)
{
    if ( ContainsPoint( pt ) )
    {
        m_bPressed = true;

        if( !m_bHasFocus )
            m_pParentDialog->RequestFocus( this );

        return true;

    }
    return false;
}

//-----------------------------------------------------------------------------
// Name : Released ()
//-----------------------------------------------------------------------------
bool CheckboxUI::Released(Point pt)
{
    if (m_bPressed)
    {
        m_bPressed = false;

        if (ContainsPoint(pt))
        {
            m_bChecked = !m_bChecked;
            m_clickedSig(this);
        }

        return true;
    }
    return false;
}

//-----------------------------------------------------------------------------
// Name : SaveToFile ()
//-----------------------------------------------------------------------------
bool CheckboxUI::SaveToFile(std::ostream& SaveFile)
{
    ButtonUI::SaveToFile(SaveFile);
    SaveFile << m_bChecked << "| is CheckBox Checked" << "\n";

    return true;
}

//-----------------------------------------------------------------------------
// Name : getChecked ()
//-----------------------------------------------------------------------------
bool CheckboxUI::getChecked()
{
    return m_bChecked;
}
