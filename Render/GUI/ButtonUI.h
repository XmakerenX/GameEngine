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

#ifndef  _BUTTONUI_H
#define  _BUTTONUI_H

#include "../RenderTypes.h"
#include "../../AssetLoading/AssetManager.h"
#include "../../timer.h"
#include "StaticUI.h"

class ButtonUI : public StaticUI
{
public:
    typedef boost::signals2::signal<void (ButtonUI*)>  signal_clicked;

                    ButtonUI            (DialogUI* pParentDialog, int ID, const std::string& strText, int x, int y, GLuint width, GLuint height, GLuint nHotkey);
                    ButtonUI            (std::istream& inputFile);
    virtual         ~ButtonUI           (void);

    virtual void    Render              (Sprite sprites[SPRITES_SIZE], Sprite topSprites[SPRITES_SIZE], double timeStamp);

    virtual bool    handleKeyEvent      (unsigned char key, bool down);
    virtual bool    handleMouseEvent    (MouseEvent event, const ModifierKeysStates &modifierStates);
    virtual bool    Pressed             (Point pt, const ModifierKeysStates &modifierStates, double timeStamp);
    virtual bool    Released            (Point pt);

    virtual bool    CanHaveFocus        ();
            void    setHotKey           (GLuint nHotKey);

    virtual bool    SaveToFile          (std::ostream& SaveFile);

            void    connectToClick      (const signal_clicked::slot_type& subscriber);



protected:
    GLuint          m_nHotkey;
    bool            m_bPressed;

    boost::signals2::signal<void (ButtonUI*)> m_clickedSig;

private:
    enum ELEMENTS{BUTTON, MOUSEOVER};
};

#endif  //_BUTTONUI_H
