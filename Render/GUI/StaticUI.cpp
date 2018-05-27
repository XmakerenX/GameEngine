#include "StaticUI.h"
#include "DialogUI.h"

//-----------------------------------------------------------------------------
// Name : StaticUI (Constructor)
//-----------------------------------------------------------------------------
StaticUI::StaticUI(DialogUI* pParentDialog, int ID, const std::string& strText, int x, int y, GLuint width, GLuint height)
    :ControlUI(pParentDialog, ID, x, y, width, height)
{
    //sets the Control type
    m_type = ControlUI::STATIC;
    m_strText = strText;
    //sets the color by Default to white
    m_textColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
}

//-----------------------------------------------------------------------------
// Name : StaticUI (constructor from InputFile)
//-----------------------------------------------------------------------------
StaticUI::StaticUI(std::istream& inputFile)
    :ControlUI(inputFile)
{
    m_type = STATIC;

    std::string controlText;

    std::getline(inputFile, controlText);
    controlText = controlText.substr(0, controlText.find('|') );
    m_strText = controlText;
    inputFile >> m_textColor.r;
    inputFile >> m_textColor.g;
    inputFile >> m_textColor.b;
    inputFile >> m_textColor.a;
    inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skips to next line
}

//-----------------------------------------------------------------------------
// Name : StaticUI (Destructor)
//-----------------------------------------------------------------------------
StaticUI::~StaticUI(void)
{
}

//-----------------------------------------------------------------------------
// Name : setTextColor ()
//-----------------------------------------------------------------------------
void StaticUI::setTextColor(glm::vec4 textColor)
{
    m_textColor = textColor;
}

//-----------------------------------------------------------------------------
// Name : getText ()
//-----------------------------------------------------------------------------
const std::string StaticUI::getText() const
{
    return m_strText;
}

//-----------------------------------------------------------------------------
// Name : Render ()
// Desc : Render the text store in the static to the screen
//-----------------------------------------------------------------------------
void StaticUI::Render(Sprite& sprite, Sprite &textSprite, double timeStamp)
{
    if (m_bVisible)
    {
        // if there is no text in the static no reason to render it
        if (m_strText[0] == '\0')
            return;

        //calculate the the button rendering rect
        Rect rcWindow(m_x, m_y, m_x + m_width, m_y + m_height);

        Point dialogPos = m_pParentDialog->getLocation();
        long  dialogCaptionHeihgt =  m_pParentDialog->getCaptionHeight();
        dialogPos.y += dialogCaptionHeihgt;

        if (m_elementsFonts.size() > 0)
        {
            Rect rcTextRect(rcWindow);
            rcTextRect.offset(dialogPos.x, dialogPos.y);
            m_elementsFonts[0].font->renderToRect(textSprite, m_strText, rcTextRect, m_textColor, mkFont::TextFormat::Center);
        }
    }
}

//-----------------------------------------------------------------------------
// Name : SaveToFile ()
//-----------------------------------------------------------------------------
bool StaticUI::SaveToFile( std::ostream& SaveFile )
{
    ControlUI::SaveToFile(SaveFile);
    SaveFile << m_strText << "| Control Text" << "\n";
    SaveFile << m_textColor.r << " "<< m_textColor.g << " "<< m_textColor.b << " " << m_textColor.a << "| Control Text Color"
        << "\n";

    return true;
}
