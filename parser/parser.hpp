#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include "function/functionTable.hpp"
#include "text/replacer/replacerTable.hpp"

/// Main class for parsing an input stream and writing output
class Parser
{
public:
    /// Constructs a new parser
    Parser(const bool pFilter);
    
    /// Parses an input stream and writes HTML code to the output stream
    void parse(std::ostream& pOut, std::istream& pIn);

private:
    /// The function table for HTML block lookup
    FunctionTable mFunctionTable;

    /// The replacer table for text formatting
    ReplacerTable mReplacerTable;
};

#endif