#ifndef LIST_FUNCTION_HPP
#define LIST_FUNCTION_HPP

#include "function/function.hpp"
#include "exception/functionException.hpp"

/// Function for bullet list blocks
class ListFunction : public Function
{
public:
    /// Constructs a new header function
    ListFunction(const bool pFilter)
        : Function(pFilter)
    {
    }

    /// Emits a header block to the stream
    virtual void emit(std::ostream& pStream,
                      const std::vector<std::string>& pInput) const
    {
        pStream << "<ul>";
        newline(pStream);
        for (int i = 0; i < pInput.size(); i++)
        {
            pStream << "<li>" << pInput[i] << "</li>";
            newline(pStream);
        }
        pStream << "</ul>";
    }
};

#endif
