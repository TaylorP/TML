#ifndef LATEX_FUNCTION_HPP
#define LATEX_FUNCTION_HPP

#include "function/function.hpp"
#include "exception/functionException.hpp"

/// Function for full width LaTeX blocks
class LatexFunction : public Function
{
public:
    /// Emits a LaTeX block to the stream
    virtual void emit(std::ostream& pStream,
                      const std::vector<std::string>& pInput) const
    {
        // Validate parameter count
        if (pInput.size() != 1)
        {
            throw(FunctionException("@latex",
                                    "Function expects 1 or 2 parameters"));
        }

        // Output the LaTeX in a math block
        pStream << "<div class='math'>" << std::endl;
        pStream << pInput[0] << std::endl;
        pStream << "</div>" << std::endl;
    }
};

#endif
