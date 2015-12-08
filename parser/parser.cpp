#include "element/functionElement.hpp"
#include "element/textElement.hpp"
#include "parser/parser.hpp"
#include "text/symbols.hpp"

Parser::Parser(const bool pFilter)
    : mReplacerTable(pFilter),
      mFunctionTable(pFilter)
{
}

void Parser::parse(std::ostream& pOut, std::istream& pIn)
{
    while (true)
    {
        int c = pIn.peek();
        if (pIn.eof())
        {
            break;
        }
        else if (Symbols::isSpace(c))
        {
            pIn.ignore();
            continue;
        }
        else if (Symbols::isFunc(c))
        {
            FunctionElement element;
            pIn >> element;
            mFunctionTable.emit(pOut, element.name(), element.params());
        }
        else
        {
            TextElement element;
            pIn >> element;

            std::stringstream output;
            mReplacerTable.replace(output, element.text());

            std::vector<std::string> params;
            params.push_back(output.str());
            
            mFunctionTable.emit(pOut, "text", params);
        }
    }
}