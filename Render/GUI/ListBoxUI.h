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

#ifndef  _LISTBOXUI_H
#define  _LISTBOXUI_H

#include "ControlUI.h"
#include "ScrollBarUI.h"

//-------------------------------------------------------------------------
//structs for This Class.
//-------------------------------------------------------------------------
template<class T>
struct Item
{
    Item(std::string text, T& newData) : strText(text), data(newData)
    {
        bVisible = false;
        bSelected = false;
    }

    Item(std::string text, T&& newData) : strText(text), data(newData)
    {
        bVisible = false;
        bSelected = false;
    }

    std::string strText;
    T data;

    Rect rcActive;
    bool bVisible;
    bool bSelected;
};

template<class T>
class ListBoxUI : public ControlUI
{
public:
    typedef boost::signals2::signal<void (ListBoxUI<T>*)> signal_listbox;
    //-------------------------------------------------------------------------
    // Constructors & Destructors for This Class.
    //-------------------------------------------------------------------------
    ListBoxUI(DialogUI *pParentDialog, int ID, int x, int y, int width, int height, bool multiSelection);
    ListBoxUI(std::istream& inputFile);
    virtual ~ListBoxUI();

    virtual bool onInit();
    //-------------------------------------------------------------------------
    //functions that handle user Input to this control
    //-------------------------------------------------------------------------
    virtual bool    handleMouseEvent(MouseEvent event, const ModifierKeysStates &modifierStates);

    virtual bool    Pressed     (Point pt, const ModifierKeysStates &modifierStates, double timeStamp);
    virtual bool    Scrolled    (int nScrollAmount);
            bool    Highlight   (Point mousePoint);

            void    ConnectToItemDoubleClick(const typename signal_listbox::slot_type& subscriber);
            void    ConnectToListboxChanged (const typename signal_listbox::slot_type& subscriber);

    //-------------------------------------------------------------------------
    //functions that handle control Rendering
    //-------------------------------------------------------------------------
    virtual void    Render           (Sprite sprites[SPRITES_SIZE], Sprite topSprites[SPRITES_SIZE], double timeStamp);
    virtual void    UpdateRects	     ();

    virtual bool    CanHaveFocus     ();

    virtual bool    SaveToFile	     (std::ostream& SaveFile);
            void    CopyItemsFrom    (ListBoxUI<T> &sourceItems);

    //-------------------------------------------------------------------------
    //functions that handle the items in the itembox
    //-------------------------------------------------------------------------
    bool            AddItem             (std::string strText, T& data);
    bool            AddItem             (std::string strText, T&& data);
    bool            InsertItem          (int nIndex, std::string &strText, T& data );
    bool            InsertItem          (int nIndex, std::string &strText, T&& data );
    void            RemoveItem          (GLuint index);
    void            RemoveItemByData	(T& data );
    void            RemoveAllItems      ();
    int             FindItem            (std::string strText, GLuint iStart = 0);
    bool            ContainsItem        (std::string strText, GLuint iStart = 0);
    Item<T>*        GetItem             (GLuint nIndex);
    T*              GetItemData         (std::string strText);
    T*              GetItemData         (int nIndex);

    const std::vector<int>& GetSelectedIndices() const;

    bool            SelectItem          (GLuint index, bool select);
    bool            SelectItem          (std::string strText, bool select);

    GLuint          GetNumItems         ();
    void            ShowItem            (int nIndex);

    int             GetScrollBarWidth   () const;
    void            SetScrollBarWidth   (int nWidth);

private:
    enum ELEMENTS {MAIN, SELECTION};

    bool m_isMultiSelection;
    int m_nSelected;    // the index from which shift drag will start
    std::vector<Item<T>> m_Items;
    std::vector<int> m_selectedItems;

    Rect m_rcItembox;
    Rect m_rcItemboxText;

    ScrollBarUI m_ScrollBar;

    signal_listbox m_itemDoubleClickSig;
    signal_listbox m_listboxChangedig;

};

#endif  //_LISTBOXUI_H
