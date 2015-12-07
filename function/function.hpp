#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <iostream>
#include <vector>

/// Base class for functions that emit HTML for a given list of inputs
class Function
{
public:
    /// Emits HTML to stream, given a list of inputs
    virtual void emit(std::ostream& pStream,
                      const std::vector<std::string>& pInput) const = 0;
};

#endif
