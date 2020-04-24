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

#ifndef  _CONTROLUI_H
#define  _CONTROLUI_H

#include <fstream>
#include <boost/signals2/signal.hpp>
#include <boost/bind/bind.hpp>
#include "../RenderTypes.h"
#include "../../Input/input.h"
#include "../../Input/mouseEventsGame.h"
#include "../../timer.h"
#include "../../AssetLoading/AssetManager.h"
#include "../Sprite.h"
#include "../Font.h"


//-----------------------------------------------------------------------------
// Typedefs, Structures and Enumerators
//-----------------------------------------------------------------------------
struct ELEMENT_FONT
{
    ELEMENT_FONT()
    {
        font = nullptr;
    }

    ELEMENT_FONT(FontInfo newFontInfo, mkFont* newFont)
        :fontInfo(newFontInfo)
    {
        font = newFont;
    }

    void setFont(FontInfo& newFontInfo, mkFont* newFont)
    {
        fontInfo = newFontInfo;
        font = newFont;
    }

    FontInfo fontInfo;
    mkFont* font;
};

struct ELEMENT_GFX
{
    ELEMENT_GFX()
    {}

    ELEMENT_GFX(Texture newTexture, Rect newRcTexture)
    {
        setGFX(newTexture, newRcTexture);
    }

    void setGFX(Texture newTexture, Rect newRcTexture)
    {
        texture = newTexture;
        rcTexture = newRcTexture;
    }

    Texture texture;
    Rect rcTexture;

};

//-----------------------------------------------------------------------------
// Classes forward declaration
//-----------------------------------------------------------------------------
class DialogUI;

//-----------------------------------------------------------------------------
// CControlUI Class declaration
//-----------------------------------------------------------------------------
class ControlUI
{
public:
    //-----------------------------------------------------------------------------
    // Public Enumerators
    //-----------------------------------------------------------------------------
    enum CONTROLS{STATIC, BUTTON, CHECKBOX, RADIOBUTTON, COMBOBOX, LISTBOX, EDITBOX,SLIDER, SCROLLBAR};
    enum SPRITES_TYPES{NORMAL = 0, TEXT, SPRITES_SIZE};

    ControlUI(void);
    ControlUI(DialogUI* pParentDialog, int ID, int x, int y, GLuint width, GLuint height);
    ControlUI(std::istream& inputFile);

    virtual ~ControlUI(void);

    virtual bool onInit();

    //-------------------------------------------------------------------------
    // functions that handle user input
    //-------------------------------------------------------------------------
    virtual bool        handleKeyEvent      (unsigned char key , bool down);
    virtual bool        handleVirtualKey    (GK_VirtualKey virtualKey , bool down, const ModifierKeysStates &modifierStates);
    virtual bool        handleMouseEvent    (MouseEvent event, const ModifierKeysStates &modifierStates);

    virtual bool        Pressed             (Point pt, const ModifierKeysStates &modifierStates, double timeStamp);
    virtual bool        Released            (Point pt);
    virtual bool        Scrolled            (int nScrollAmount);
    virtual bool        Dragged             (Point pt);
                                                                                                                           
    virtual void        Render              (Sprite sprites[SPRITES_SIZE], Sprite topSprites[SPRITES_SIZE], double timeStamp) = 0;

            void        renderRect          (Sprite& sprite, const Rect &rcWindow, const Texture& texture, const Rect &rcTexture, glm::vec4 color, Point offset);
            void        renderText          (Sprite& textSprite, mkFont* font, std::string text, glm::vec4 color , Rect &rcText, Point dialogPos,
                                             mkFont::TextFormat format = mkFont::TextFormat::Center);

            Point       calcPositionOffset();

    virtual bool        ContainsPoint     (Point pt);

    virtual void        onMouseEnter      ();
    virtual void        onMouseLeave      ();

    virtual bool        CanHaveFocus      ();
    virtual void        OnFocusIn         ();
    virtual void        OnFocusOut        ();

            void        SetID             (int ID);
            void        setLocation       (int x, int y);
            void        setSize           (GLuint width, GLuint height);
            void        setParent         (DialogUI* pParentDialog);
            void        setControlGFX     (std::vector<ELEMENT_GFX>& elementsGFX);
            void        setControlFonts   (std::vector<ELEMENT_FONT>& elementsFonts);
            void        setEnabled        (bool bEnabled);
            void        setVisible        (bool bVisible);

            int         getID             () const;
            GLuint      getType           () const;
            bool        getEnabled        () const;
            bool        getVisible        () const;
            int         getX              () const;
            int         getY              () const;
            int         getWidth          () const;
            int         getHeight         () const;
            DialogUI *  getParentDialog   () const;

    virtual bool	SaveToFile        (std::ostream& SaveFile);

    virtual void        UpdateRects       ();
protected:

    DialogUI* m_pParentDialog;

    // Size, scale, and positioning members
    int m_x, m_y;
    int m_width, m_height;

    int m_ID;
    GLuint m_type;

    Rect m_rcBoundingBox;           // Rectangle defining the active region of the control

    bool m_bVisible;                // Shown/hidden flag
    bool m_bEnabled;                // Enabled/disabled flag

    bool m_bMouseOver;              // Mouse pointer is above control
    bool m_bHasFocus;               // Control has input focus;

    std::vector<ELEMENT_GFX>  m_elementsGFX;
    std::vector<ELEMENT_FONT> m_elementsFonts;
};

#endif  //_CONTROLUI_H

