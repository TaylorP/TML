#ifndef CODE_FUNCTION_HPP
#define CODE_FUNCTION_HPP

#include "function/function.hpp"
#include "exception/functionException.hpp"

/// Function for full width code blocks
class CodeFunction : public Function
{
public:
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
        pStream << "<pre class='prettyprint linenums " << pInput[0]
                << "'>" << std::endl;

        // Print the code
        pStream << pInput[1] << std::endl;

        // Close the pre tag
        pStream << "</pre>" << std::endl;
    }
};

#endif
