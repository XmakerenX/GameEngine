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

#ifndef  _SLIDERUI_H
#define  _SLIDERUI_H

#include "ControlUI.h"

class SliderUI : public ControlUI
{
public:

    typedef boost::signals2::signal<void (SliderUI*)>  signal_slider;
    //-------------------------------------------------------------------------
    // Constructors & Destructors for This Class.
    //-------------------------------------------------------------------------
                    SliderUI            (DialogUI* pParentDialog, int ID, int x, int y, int width, int height, int min, int max, int nValue );
                    SliderUI            (std::istream& inputFile);
    virtual         ~SliderUI           (void);

    virtual bool    ContainsPoint       (Point pt);

    //-------------------------------------------------------------------------
    // functions that handle user input to the control
    //-------------------------------------------------------------------------
    virtual bool    handleMouseEvent    (MouseEvent event, const ModifierKeysStates &modifierStates);
    virtual bool    Pressed             (Point pt, const ModifierKeysStates &modifierStates, double timeStamp);
    virtual bool    Released            (Point pt);
    virtual bool    Scrolled            (int nScrollAmount);
    virtual bool    Dragged             (Point pt);

            void    connectToSliderChg  (const signal_slider::slot_type& subscriber);

    //-------------------------------------------------------------------------
    // functions that handle Rendering
    //-------------------------------------------------------------------------
    virtual void    UpdateRects         ();
    virtual bool    CanHaveFocus        ();

    virtual bool    SaveToFile          (std::ostream& SaveFile);

    virtual void    Render              (Sprite sprites[SPRITES_SIZE], Sprite topSprites[SPRITES_SIZE], double timeStamp);

            void    SetValue            (int nValue);
            int     GetValue            () const;

            void    GetRange            (int& nMin, int& nMax) const;
            void    SetRange            (int nMin, int nMax);

protected:
            void    SetValueInternal    (int nValue, bool bFromInput);
            int     ValueFromPos        (int x);

            int m_nValue;

            int m_nMin;
            int m_nMax;

            int m_nDragX;      // Mouse position at start of drag
            int m_nDragOffset; // Drag offset from the center of the button
            int m_nButtonX;

            bool m_bPressed;

            boost::signals2::signal<void (SliderUI*)> m_sliderChangedSig;

            Rect m_rcButton;

private:
            enum ELEMENTS{TRACK, BUTTON};
};

#endif  //_SLIDERUI_H
