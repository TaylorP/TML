#ifndef REPLACER_TABLE_HPP
#define REPLACER_TABLE_HPP

#include <iostream>
#include <vector>

#include "text/replacer/replacer.hpp"

/// Table of replacers. Performs text replacement with a single pass over the 
/// input stream.
class ReplacerTable
{
public:
    /// Constructs a new replacer table instance
    ReplacerTable();

    /// Destroys a replacer table
    ~ReplacerTable();

    /// Runs all replacers on the given text stream
    void replace(std::ostream& pOut, std::istream& pIn);

    /// Runs the replacers on an input string instead of a stream
    void replace(std::ostream& pOut, const std::string& pString);

private:

    /// The list of replacers
    std::vector<Replacer*> mReplacers;

    /// Resets all of the replacers
    void reset();

    /// Verifies all of the replacers
    void verify() const;
};

#endif