#ifndef FUNCTION_ELEMENT_HPP
#define FUNCTION_ELEMENT_HPP

#include <string>
#include <vector>

#include "element/element.hpp"

/// Function element
class FunctionElement : public Element
{
public:
    /// Constructs a new function element
    FunctionElement();

    /// Returns the function name
    inline const std::string& name() const
    {
        return mName;
    }

    /// Returns the function parameters
    inline const std::vector<std::string>& params() const
    {
        return mParams;
    }

private:
    /// Function state machine/DFA states
    enum State
    {
        eFunctionEntry,
        eFunctionLabel,
        eParamEntry,
        eParamLabel,
        eParamExit
    };

    /// The current parsing state
    State mState;

    /// The function name
    std::string mName;

    /// The function parameter list
    std::vector<std::string> mParams;

    /// Parses an element from an input stream
    virtual void parse(std::istream& pStream);

    /// Prints the text element to the stream
    virtual void print(std::ostream& pStream) const;
};

#endif