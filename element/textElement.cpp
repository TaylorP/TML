#include "element/textElement.hpp"
#include "text/colors.hpp"
#include "text/symbols.hpp"

TextElement::TextElement()
    : mText("")
{
}

void TextElement::parse(std::istream& pStream)
{
    int newLine = false;
    std::stringstream text;

    while (true)
    {
        int symbol = Symbols::readSymbol(pStream, false);

        if (symbol == EOF)
        {
            break;
        }
        else if (Symbols::isNewline(symbol))
        {
            if (newLine)
            {
                break;
            }

            newLine = true;
        }
        else
        {
            if (newLine)
            {
                text << '\n';
            }

            newLine = false;
            text << (char)(symbol);
        }
    }

    mText = text.str();
}

void TextElement::print(std::ostream& pStream) const
{
    pStream << Colors::green() << "TextElement: "
            << Colors::reset();

    pStream << mText.substr(0, 20);

    if (mText.length() > 20)
    {
        pStream << "...";
    }
}