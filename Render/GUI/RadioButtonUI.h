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

#ifndef  _RADIOBUTTONUI_H
#define  _RADIOBUTTONUI_H

#include "CheckboxUI.h"

class RadioButtonUI : public CheckboxUI
{
public:
                    RadioButtonUI       (DialogUI* pParentDialog, int ID, int x, int y, GLuint width, GLuint height, GLuint nHotkey, GLuint nButtonGruop);
                    RadioButtonUI       (std::istream& inputFile);
    virtual         ~RadioButtonUI      (void);

    virtual bool    handleMouseEvent    (MouseEvent event, const ModifierKeysStates &modifierStates);

    virtual bool    Pressed             (Point pt, const ModifierKeysStates &modifierStates, double timeStamp);
    virtual bool    Released            (Point pt);

    virtual bool    SaveToFile          (std::ostream& SaveFile);

            GLuint  getButtonGroup      ();

            void    setChecked          (bool bChecked);
            void    setButtonGroup      (GLuint buttonGroup);

protected:
    GLuint m_nButtonGroup;
};

#endif  //_RADIOBUTTONUI_H

 
