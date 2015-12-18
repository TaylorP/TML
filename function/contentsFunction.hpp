#ifndef CONTENTS_FUNCTION_HPP
#define CONTENTS_FUNCTION_HPP

#include "function/function.hpp"
#include "exception/functionException.hpp"

/// Function for table of contents lists
class ContentsFunction : public Function
{
public:
    /// Constructs a new contents function
    ContentsFunction(const bool pFilter)
        : Function(pFilter)
    {
    }

    /// Emits an image block to the stream
    virtual void emit(std::ostream& pStream,
                      const std::vector<std::string>& pInput) const
    {
        // Validate parameter count
        if (pInput.size() < 2 || (pInput.size() % 2) != 0)
        {
            throw(FunctionException("@contents",
                                    "Function expects 1 or more name + link pairs"));
        }

        // Print the centering block
        pStream << "<div class='contents'>";
        newline(pStream);

        // Print the list start
        pStream << "<ul>";
        newline(pStream);

        // Print the entries
        for (int i = 0; i < pInput.size(); i+=2)
        {
            if (pInput[i+1].length() > 0)
            {
                pStream << "<a href='" << pInput[i+1] << "'><li>"
                        << pInput[i] << "</li></a>";
            }
            else
            {
                pStream << "<li>"
                        << pInput[i] << "</li>"; 
            }

            newline(pStream);
        }

        // Close the list
        pStream << "</ul>";
        newline(pStream);

        // Close the center block
        pStream << "</div>";
        newline(pStream);
    }
};

#endif
