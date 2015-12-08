#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <iostream>
#include <vector>

/// Base class for functions that emit HTML for a given list of inputs
class Function
{
public:
    /// Constructs a new function
    Function(const bool pFilter)
        : mFilter(pFilter)
    {
    }

    /// Emits HTML to stream, given a list of inputs
    virtual void emit(std::ostream& pStream,
                      const std::vector<std::string>& pInput) const = 0;

protected:
    /// Emits a newline if the filter isn't set
    inline void newline(std::ostream& pStream) const
    {
        if (!mFilter)
        {
            pStream << std::endl;
        }
    }

    /// Set to true if newlines should be filtered out
    bool mFilter;
};

#endif
