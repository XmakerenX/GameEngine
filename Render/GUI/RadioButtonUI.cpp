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

#include "RadioButtonUI.h"
#include "DialogUI.h"

//-----------------------------------------------------------------------------
// Name : RadioButtonUI (Constructor)
//-----------------------------------------------------------------------------
RadioButtonUI::RadioButtonUI(DialogUI* pParentDialog, int ID, int x, int y, GLuint width, GLuint height, GLuint nHotkey, GLuint nButtonGruop)
    :CheckboxUI(pParentDialog, ID, x, y, width, height, nHotkey)
{
    m_type = RADIOBUTTON;
    m_nButtonGroup = nButtonGruop;
}

//-----------------------------------------------------------------------------
// Name : CRadioButtonUI (constructor from InputFile)
//-----------------------------------------------------------------------------
RadioButtonUI::RadioButtonUI(std::istream& inputFile)
    :CheckboxUI(inputFile)
{
    m_type = RADIOBUTTON;

    inputFile >> m_nButtonGroup;
    inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skips to next line
}
//-----------------------------------------------------------------------------
// Name : CRadioButtonUI (destructor)
//-----------------------------------------------------------------------------
RadioButtonUI::~RadioButtonUI(void)
{
}

//-----------------------------------------------------------------------------
// Name : handleMouseEvent ()
//-----------------------------------------------------------------------------
bool RadioButtonUI::handleMouseEvent(MouseEvent event, const ModifierKeysStates &modifierStates)
{
    if (!m_bEnabled || !m_bVisible)
        return false;

    switch(event.type)
    {
    case MouseEventType::LeftButton:
    {
        if (event.down)
        {
            if ( Pressed(event.cursorPos, modifierStates, event.timeStamp))
                return true;
        }
        else
        {
            if ( Released(event.cursorPos))
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
bool RadioButtonUI::Pressed(Point pt, const ModifierKeysStates &modifierStates, double timeStamp)
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
bool RadioButtonUI::Released(Point pt)
{
    if (m_bPressed)
    {
        m_bPressed = false;

        if (ContainsPoint(pt))
        {
            m_pParentDialog->ClearRadioButtonGruop(m_nButtonGroup);
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
bool RadioButtonUI::SaveToFile(std::ostream& SaveFile)
{
    CheckboxUI::SaveToFile(SaveFile);

    SaveFile << m_nButtonGroup << "| RadioButton Button Group" << "\n";

    return true;
}

//-----------------------------------------------------------------------------
// Name : getButtonGroup ()
//-----------------------------------------------------------------------------
GLuint RadioButtonUI::getButtonGroup()
{
    return m_nButtonGroup;
}

//-----------------------------------------------------------------------------
// Name : setChecked ()
//-----------------------------------------------------------------------------
void RadioButtonUI::setChecked(bool bChecked)
{
    m_bChecked = bChecked;
}

//-----------------------------------------------------------------------------
// Name : setButtonGroup ()
//-----------------------------------------------------------------------------
void RadioButtonUI::setButtonGroup(GLuint buttonGroup)
{
    m_nButtonGroup = buttonGroup;
}
