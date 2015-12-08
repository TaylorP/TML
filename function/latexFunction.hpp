#ifndef LATEX_FUNCTION_HPP
#define LATEX_FUNCTION_HPP

#include "function/function.hpp"
#include "exception/functionException.hpp"

/// Function for full width LaTeX blocks
class LatexFunction : public Function
{
public:
    /// Constructs a new latex function
    LatexFunction(const bool pFilter)
        : Function(pFilter)
    {
    }

    /// Emits a LaTeX block to the stream
    virtual void emit(std::ostream& pStream,
                      const std::vector<std::string>& pInput) const
    {
        // Validate parameter count
        if (pInput.size() != 1)
        {
            throw(FunctionException("@latex",
                                    "Function expects exactly 1 parameter"));
        }

        // Output the LaTeX in a math block
        pStream << "<div class='math'>";
        newline(pStream);

        pStream << pInput[0];
        newline(pStream);
        
        pStream << "</div>";
        newline(pStream);
    }
};

#endif
