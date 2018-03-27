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
{
}

//-----------------------------------------------------------------------------
// Name : Render ()
// Desc : renders the button
//-----------------------------------------------------------------------------
void ButtonUI::Render( Sprite& sprite, AssetManager& assetManger)
{
    if (m_bVisible)
    {
        //GLuint textureName;

        //no texture was given abort rendering
        if (m_elementsGFX.size() < 2 ||m_elementsGFX[BUTTON].iTexture == -1 || m_elementsGFX[MOUSEOVER].iTexture == -1)
            return;

        //acquire a pointer to the texture we need to render the button
        //textureName = assetManger.getTexturePtr(m_elementsGFX[0].iTexture);

        Point dialogPos = m_pParentDialog->getLocation();
        long  dialogCaptionHeihgt =  m_pParentDialog->getCaptionHeight();
        dialogPos.y += dialogCaptionHeihgt;

        //calculate the the button rendering rect
        Rect rcWindow(m_x, m_y, m_width, m_height);

        //if the button is not pressed or doesn't have the cursor on it render it normally
        if (!m_bMouseOver)
        {
            if (!m_bEnabled)
                renderRect(sprite, rcWindow, m_elementsGFX[BUTTON].iTexture, m_elementsGFX[BUTTON].rcTexture, glm::vec4( 1.0f, 0.4f, 0.4f, 0.4f ), dialogPos);
                //renderRect(m_elementsGFX[BUTTON].rcTexture, rcWindow, sprite, textureName, glm::vec4( 255, 100, 100, 100 ), REGLUAR, dialogPos);
            else
                renderRect(sprite, rcWindow, m_elementsGFX[BUTTON].iTexture, m_elementsGFX[BUTTON].rcTexture, glm::vec4( 1.0f, 0.785f, 0.785f, 0.785f ), dialogPos);
                //renderRect(m_elementsGFX[BUTTON].rcTexture, rcWindow, sprite, textureName, glm::vec4( 255, 200, 200, 200 ), REGLUAR, dialogPos );
        }
        else
        {
            // if the button is pressed and the cursor is on it darken it to showed it is pressed
            if (m_bMouseOver && m_bPressed)
                renderRect(sprite, rcWindow, m_elementsGFX[MOUSEOVER].iTexture, m_elementsGFX[MOUSEOVER].rcTexMouseOver, glm::vec4( 1.0f, 0.6f, 0.6f, 0.6f ), dialogPos);
                //renderRect(m_elementsGFX[MOUSEOVER].rcTexMouseOver, rcWindow, sprite, textureName, D3DCOLOR_ARGB( 255, 150, 150, 150 ), REGLUAR, dialogPos );
            else
                // if the button has the cursor on it high light
                if (m_bMouseOver)
                    renderRect(sprite, rcWindow, m_elementsGFX[MOUSEOVER].iTexture, m_elementsGFX[MOUSEOVER].rcTexMouseOver, glm::vec4( 1.0f, 1.0f, 1.0f, 1.0f ), dialogPos);
                    //renderRect(m_elementsGFX[MOUSEOVER].rcTexMouseOver, rcWindow, sprite, textureName, D3DCOLOR_ARGB( 255, 255, 255, 255 ), HiGHLIGHT, dialogPos);
        }

//        LPD3DXFONT pFont;
//        //acquire a pointer to the font we need to use to render the text
//        if (m_elementsFonts.size() > 0)
//            pFont = assetManger.getFontPtr(m_elementsFonts[0].fontIndex);
//        else
//            return;

        // continue to render the text only if we got a valid pointer
//        if (pFont)
//        {
//            LPD3DXSPRITE pSprite = assetManger.getSprite();

//            if (!pSprite)
//                return;

//            SetRect(&rcWindow, 0, 0, m_width, m_height);
//            OffsetRect(&rcWindow, m_x + dialogPos.x, m_y + dialogPos.y);

//            D3DXMATRIXA16 matTransform;
//            D3DXMatrixScaling( &matTransform, 1.0f, 1.0f, 1.0f );

//            pSprite->SetTransform( &matTransform );

//            pFont->DrawTextA(pSprite, m_strText, -1, &rcWindow, DT_NOCLIP | DT_CENTER | DT_VCENTER, m_textColor);
//        }
    }
}

//-----------------------------------------------------------------------------
// Name : HandleMouse ()
// Desc : handles mouse events for this button
//-----------------------------------------------------------------------------
bool ButtonUI::HandleMouse(GLuint uMsg, Point mousePoint, INPUT_STATE inputstate, Timer* timer )
{
//    if (!m_bEnabled || !m_bVisible)
//        return false;

//    switch(uMsg)
//    {
//    case WM_LBUTTONDOWN:
//    case WM_LBUTTONDBLCLK:
//        {
//            if (Pressed(hWnd, mousePoint, inputstate, timer))
//                return true;
//        }break;

//    case WM_LBUTTONUP:
//        {
//            if (Released(hWnd, mousePoint))
//                return true;
//        }break;
//    }

    return false;
}

//-----------------------------------------------------------------------------
// Name : HandleKeyboard ()
// Desc : handles keyboard events for this button
//-----------------------------------------------------------------------------
//bool ButtonUI::HandleKeyboard(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
//{
//    switch(uMsg)
//    {
//    case WM_KEYDOWN:
//        {
//            switch(wParam)
//            {
//            case VK_SPACE:
//                m_bPressed = true;
//                return true;
//            };
//        }break;

//    case WM_KEYUP:
//        {
//            switch(wParam)
//            {
//            case VK_SPACE:
//                {
//                    if ( m_bPressed == true )
//                    {
//                        m_bPressed = false;
//                        m_pParentDialog->SendEvent(1, true, m_ID, hWnd);
//                        return true;
//                    }
//                }break;
//            }
//        }

//    }

//    return false;
//}

//-----------------------------------------------------------------------------
// Name : Pressed ()
//-----------------------------------------------------------------------------
//bool ButtonUI::Pressed( HWND hWnd, Point pt, INPUT_STATE inputState, Timer* timer)
//{
//    if ( ContainsPoint( pt ) )
//    {
//        m_bPressed = true;

//        SetCapture(hWnd);

//        if( !m_bHasFocus )
//            m_pParentDialog->RequestFocus( this );

//        return true;
//    }
//    return false;
//}

//-----------------------------------------------------------------------------
// Name : Released ()
//-----------------------------------------------------------------------------
//bool ButtonUI::Released(HWND hWnd, POINT pt)
//{
//    if (m_bPressed)
//    {
//        m_bPressed = false;
//        ReleaseCapture();

//        //TODO: something here about keyboard input from dialog...

//        if (ContainsPoint(pt))
//            m_clickedSig(this);
//            //m_pParentDialog->SendEvent(1, true, m_ID, hWnd);

//        return true;
//    }
//    return false;
//}

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
    StaticUI::SaveToFile(SaveFile);

    SaveFile << m_nHotkey << "| Button HotKey" << "\n";

//TODO: add the abilty to save custom buttons
// 	if  ( isControlDefualt() )
// 	{
// 		outputFile << "1" << " Control Default" << "\n";
// 	}
// 	else
// 	{
// 		outputFile << "0" << " Control Default" << "\n";
// 	}
    return true;
}

//-----------------------------------------------------------------------------
// Name : CanHaveFocus ()
//-----------------------------------------------------------------------------
bool ButtonUI::CanHaveFocus()
{
    return ( m_bVisible && m_bEnabled );
}
