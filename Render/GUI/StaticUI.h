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

#ifndef  _STATICUI_H
#define  _STATICUI_H

#include <string>
#include "ControlUI.h"

class StaticUI : public ControlUI
{
public:
                            StaticUI            (DialogUI* pParentDialog, int ID, const std::string &strText, int x, int y, GLuint width, GLuint height);
                            StaticUI            (std::istream& inputFile);
    virtual                 ~StaticUI           (void);

                void        setTextColor        (glm::vec4 textColor);
                void        setText             (const std::string& text);
                void        setTextOrientation  (mkFont::TextFormat textOrientation);
    const       std::string getText             () const;

                void        Render              (Sprite sprites[SPRITES_SIZE], Sprite topSprites[SPRITES_SIZE], double timeStamp);

    virtual     bool        SaveToFile          (std::ostream& SaveFile);

protected:
    std::string m_strText;
    glm::vec4   m_textColor;
    mkFont::TextFormat m_textOrientation;
};

#endif  //_STATICUI_H
