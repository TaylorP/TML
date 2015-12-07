#include "element/functionElement.hpp"
#include "exception/genericException.hpp"
#include "text/colors.hpp"
#include "text/symbols.hpp"

FunctionElement::FunctionElement()
    : mState(eFunctionEntry), mName("")
{
}

void FunctionElement::parse(std::istream& pStream)
{
    // Ignore the ampersand character
    pStream.ignore();

    // The function name and parameter string stream
    std::stringstream parseStream;

    // Parse the function
    while (true)
    {
        int symbol;
        Symbols::readSymbol(pStream, symbol);

        char character = char(symbol);
        switch (mState)
        {
            case eFunctionEntry:
            {
                if (Symbols::isLetter(character))
                {
                    mState = eFunctionLabel;
                    parseStream << character;
                }
                else
                {
                    throw(GenericException(
                        "Function names must only consist of letters"));
                }

                break;
            }

            case eFunctionLabel:
            {
                if (Symbols::isLetter(character))
                {
                    parseStream << character;
                }
                else if (Symbols::isOpen(character))
                {
                    mState = eParamEntry;
                    mName = parseStream.str();
                    parseStream.str("");
                }
                else
                {
                    throw(GenericException(
                        "Function ame must be a sequence of letters, followed by a ("));
                }

                break;
            }

            case eParamEntry:
            {
                if (Symbols::isSpace(character))
                {
                    // pass
                }
                else if (Symbols::isQuote(character))
                {
                    mState = eParamLabel;
                }
                else
                {
                    throw(GenericException(
                        "Parameter must begin with an open quote symbol: \'"));
                }

                break;
            }

            case eParamLabel:
            {
                if (Symbols::isQuote(character))
                {
                    mState = eParamExit;
                    mParams.push_back(parseStream.str());
                    parseStream.str("");
                }
                else
                {
                    parseStream << character;
                }

                break;
            }

            case eParamExit:
            {
                if (Symbols::isSpace(character))
                {
                    // pass
                }
                else if (Symbols::isDelim(character))
                {
                    mState = eParamEntry;
                }
                else if (Symbols::isClosed(character))
                {
                    return;
                }
                else
                {
                    throw(GenericException(
                        "Parameter must be followed by , or )"));
                }

                break;
            }

            default:
            {
                throw(GenericException("Invalid parse state"));
            }
        }
    }
}

void FunctionElement::print(std::ostream& pStream) const
{
    pStream << Colors::green() << "FunctionElement: "
            << Colors::reset();
    pStream << mName << "(";

    for (int i = 0; i < mParams.size(); i++)
    {
        if (i > 0)
        {
            pStream << ", ";
        }

        pStream << mParams[i];
    }

    pStream << ")";
}