#ifndef TEXT_FUNCTION_HPP
#define TEXT_FUNCTION_HPP

#include "function/function.hpp"
#include "exception/functionException.hpp"

/// Function for plain text blocks
class TextFunction : public Function
{
public:
    /// Emits a full width code block to the stream
    virtual void emit(std::ostream& pStream,
                      const std::vector<std::string>& pInput) const
    {
        // Validate parameter count
        if (pInput.size() != 1)
        {
            throw(FunctionException("@text",
                                    "Function expects exactly 1 parameter"));
        }
        
        // Print the paragraph tag
        pStream << "<p>" << std::endl;

        // Print the plain text content
        pStream << pInput[0] << std::endl;

        // Close the paragraph tag
        pStream << "</p>" << std::endl;
    }
};

#endif
