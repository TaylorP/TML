#ifndef REPLACER_HPP
#define REPLACER_HPP

#include <iostream>
#include "text/replacer/replacerState.hpp"

class ReplacerTable;

/// Abstract base class for a replacer 
class Replacer
{
public:
    /// Constructs a new replacer
    Replacer(const ReplacerTable* pTable)
        : mTable(pTable)
    {
    }

    /// Virtual destructor for clean up
    virtual ~Replacer() {}

    /// Runs the replacer on the given input. A return value of empty string
    /// indicates that no replacement was found, while any other return
    /// value will be used during replacement. pConsume indicates if the original
    /// character should be consumed.
    virtual std::string replace(const char pPrev,
                                const char pCur,
                                const char pNext,
                                const bool pSkip,
                                bool& pConsume) = 0;

    /// Returns the state of the replacer, e.g. if a code block is active
    virtual ReplacerState state() const = 0;
    
    /// Resets the replacer, called for each text blob
    virtual void reset() = 0;

    /// Verifies that the replacer completed cleanly, called at the end of
    /// each text blob.
    virtual void verify() const = 0;

protected:
    /// The replacer table instance
    const ReplacerTable* mTable;

};

#endif