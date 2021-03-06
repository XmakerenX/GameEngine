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

#include "ButtonUI.h"
#include "DialogUI.h"

//-----------------------------------------------------------------------------
// Name : CButtonUI (constructor)
//-----------------------------------------------------------------------------
ButtonUI::ButtonUI(DialogUI* pParentDialog, int ID, const std::string& strText, int x, int y, GLuint width, GLuint height, GLuint nHotkey)
    :StaticUI(pParentDialog, ID, strText, x, y, width, height)
{
    m_type = ControlUI::BUTTON;
    m_nHotkey = nHotkey;
    m_bPressed = false;
    m_textColor = glm::vec4( 1.0f, 1.0f, 1.0f, 1.0f );
    m_textOrientation = mkFont::TextFormat::Center;
}

//-----------------------------------------------------------------------------
// Name : CButtonUI (constructor from InputFile)
//-----------------------------------------------------------------------------
ButtonUI::ButtonUI(std::istream& inputFile)
    :StaticUI(inputFile)
{
    m_type = ControlUI::BUTTON;

    GLuint nHotkey;
    inputFile >> nHotkey;

    m_bPressed = false;
    setHotKey(nHotkey);
    inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skips to next line
}

//-----------------------------------------------------------------------------
// Name : CButtonUI (destructor)
//-----------------------------------------------------------------------------
ButtonUI::~ButtonUI(void)
{}

//-----------------------------------------------------------------------------
// Name : Render ()
// Desc : renders the button
//-----------------------------------------------------------------------------
void ButtonUI::Render(Sprite sprites[SPRITES_SIZE], Sprite topSprites[SPRITES_SIZE], double timeStamp)
{
    //no texture was given abort rendering
    if (m_elementsGFX.size() < 2 ||m_elementsGFX[BUTTON].texture.name == 0 || m_elementsGFX[MOUSEOVER].texture.name == 0 || !m_bVisible)
        return;

    Point dialogPos = calcPositionOffset();

    //calculate the the button rendering rect
    Rect rcWindow(m_x, m_y, m_x + m_width, m_y + m_height);

    glm::vec4 tintColor;
    if (!m_bEnabled)
        tintColor = glm::vec4(0.4f, 0.4f, 0.4f, 1.0f);
    else
        if (m_bPressed)
            tintColor = glm::vec4(0.6f, 0.6f, 0.6f, 1.0f);
        else
            if (m_bMouseOver)
                tintColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
            else
                tintColor = glm::vec4(0.785f, 0.785f, 0.785f, 1.0f);

    renderRect(sprites[NORMAL], rcWindow, m_elementsGFX[BUTTON].texture, m_elementsGFX[BUTTON].rcTexture, tintColor, dialogPos);

    if (m_elementsFonts.size() > 0)
        renderText(sprites[TEXT], m_elementsFonts[0].font, m_strText, m_textColor, rcWindow, dialogPos, m_textOrientation);

}

//-----------------------------------------------------------------------------
// Name : handleMouseEvent ()
// Desc : handles mouse events for this button
//-----------------------------------------------------------------------------
bool ButtonUI::handleMouseEvent(MouseEvent event, const ModifierKeysStates &modifierStates)
{
    if(!m_bVisible || !m_bEnabled)
        return false;
    
    switch(event.type)
    {
    case MouseEventType::LeftButton:
    case MouseEventType::DoubleLeftButton:
    {
        if (event.down)
        {
            if (Pressed(event.cursorPos, modifierStates, event.timeStamp))
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
// Name : handleKeyEvent ()
// Desc : handles key events for this button
//-----------------------------------------------------------------------------
bool ButtonUI::handleKeyEvent(unsigned char key, bool down)
{
    if(!m_bVisible || !m_bEnabled)
        return false;
        
    if (key == ' ')
    {
        if (down)
        {
            m_bPressed = true;
            return true;
        }
        else
        {
            if (m_bPressed)
            {
                m_bPressed = false;
                m_clickedSig(this);
                return true;
            }
        }
    }

    return false;
}

//-----------------------------------------------------------------------------
// Name : Pressed ()
//-----------------------------------------------------------------------------
bool ButtonUI::Pressed (Point pt, const ModifierKeysStates &modifierStates, double timeStamp)
{
    if ( ContainsPoint( pt ) )
    {
        std::cout << "Button pressed\n";
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
bool ButtonUI::Released(Point pt)
{
    if (m_bPressed)
    {
        m_bPressed = false;

        if (ContainsPoint(pt))
            m_clickedSig(this);

        return true;
    }
    return false;
}

//-----------------------------------------------------------------------------
// Name : setHotKey ()
//-----------------------------------------------------------------------------
void ButtonUI::setHotKey(GLuint nHotKey)
{
    m_nHotkey = nHotKey;
}

//-----------------------------------------------------------------------------
// Name : connectToClick ()
//-----------------------------------------------------------------------------
void ButtonUI::connectToClick(const signal_clicked::slot_type& subscriber)
{
    m_clickedSig.connect(subscriber);
}

//-----------------------------------------------------------------------------
// Name : SaveToFile ()
//-----------------------------------------------------------------------------
bool ButtonUI::SaveToFile(std::ostream& SaveFile)
{
    //TODO: add the abilty to save custom buttons
    StaticUI::SaveToFile(SaveFile);
    SaveFile << m_nHotkey << "| Button HotKey" << "\n";
    return true;
}

//-----------------------------------------------------------------------------
// Name : CanHaveFocus ()
//-----------------------------------------------------------------------------
bool ButtonUI::CanHaveFocus()
{
    return ( m_bVisible && m_bEnabled );
}
