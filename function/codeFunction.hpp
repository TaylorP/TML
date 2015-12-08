#ifndef CODE_FUNCTION_HPP
#define CODE_FUNCTION_HPP

#include "function/function.hpp"
#include "exception/functionException.hpp"

/// Function for full width code blocks
class CodeFunction : public Function
{
public:
    /// Constructs a new code function
    CodeFunction(const bool pFilter)
        : Function(pFilter)
    {
    }

    /// Emits a full width code block to the stream
    virtual void emit(std::ostream& pStream,
                      const std::vector<std::string>& pInput) const
    {
        // Validate parameter count
        if (pInput.size() != 2)
        {
            throw(FunctionException("@code",
                                    "Function expects exactly 2 parameters"));
        }
        
        // Print the pre tag, including the linenums and language class
        pStream << "<pre class='prettyprint linenums " << pInput[0] << "'>";
        newline(pStream);

        // Print the code
        pStream << pInput[1];
        newline(pStream);

        // Close the pre tag
        pStream << "</pre>";
        newline(pStream);
    }
};

#endif
