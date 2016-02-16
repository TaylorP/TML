#ifndef SUBHEADER_FUNCTION_HPP
#define SUBHEADER_FUNCTION_HPP

#include "function/function.hpp"
#include "exception/functionException.hpp"

/// Function for subheader blocks
class SubheaderFunction : public Function
{
public:
    /// Constructs a new header function
    SubheaderFunction(const bool pFilter)
        : Function(pFilter)
    {
    }

    /// Emits a header block to the stream
    virtual void emit(std::ostream& pStream,
                      const std::vector<std::string>& pInput) const
    {
        // No id was given, just a title, so print a simple header
        if (pInput.size() == 1)
        {
            pStream << "<h2>" << pInput[0] << "</h2>" << std::endl;
        }
        // Invalid parameter count
        else
        {
            throw(FunctionException("@subheader",
                                    "Function expects exactly 1 parameter"));
        }
    }
};

#endif
