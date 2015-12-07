#ifndef HEADER_FUNCTION_HPP
#define HEADER_FUNCTION_HPP

#include "function/function.hpp"
#include "exception/functionException.hpp"

/// Function for header blocks
class HeaderFunction : public Function
{
public:
    /// Emits a header block to the stream
    virtual void emit(std::ostream& pStream,
                      const std::vector<std::string>& pInput) const
    {
        // No id was given, just a title, so print a simple header
        if (pInput.size() == 1)
        {
            pStream << "<h1>" << pInput[0] << "</h1>" << std::endl;
        }
        // An id was also provided so generate a link
        else if (pInput.size() == 2)
        {
            pStream << "<h1 id='" << pInput[1] << "'>" << pInput[0] << std::endl;
            pStream << "<a href='#" << pInput[1] << "'><div class='link'></div></a>" << std::endl;
            pStream << "</h1>" << std::endl;
        }
        // Invalid parameter count
        else
        {
            throw(FunctionException("@header",
                                    "Function expects 1 or 2 parameters"));
        }
    }
};

#endif
