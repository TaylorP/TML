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
        char symbol = Symbols::readSymbol(pStream);

        switch (mState)
        {
            case eFunctionEntry:
            {
                if (Symbols::isLetter(symbol))
                {
                    mState = eFunctionLabel;
                    parseStream << symbol;
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
                if (Symbols::isLetter(symbol))
                {
                    parseStream << symbol;
                }
                else if (Symbols::isOpen(symbol))
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
                if (Symbols::isSpace(symbol))
                {
                    // pass
                }
                else if (Symbols::isQuote(symbol))
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
                if (Symbols::isQuote(symbol))
                {
                    mState = eParamExit;
                    mParams.push_back(parseStream.str());
                    parseStream.str("");
                }
                else
                {
                    parseStream << symbol;
                }

                break;
            }

            case eParamExit:
            {
                if (Symbols::isSpace(symbol))
                {
                    // pass
                }
                else if (Symbols::isDelim(symbol))
                {
                    mState = eParamEntry;
                }
                else if (Symbols::isClosed(symbol))
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