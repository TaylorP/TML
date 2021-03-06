#ifndef DASH_REPLACER_HPP
#define DASH_REPLACER_HPP

#include <iostream>
#include <unordered_map>

#include "text/replacer/replacer.hpp"

/// Replaces -- with an en-dash and --- with an em-dash
class DashReplacer : public Replacer
{
public:
    /// Constructs a new dash replacer
    DashReplacer(const ReplacerTable* pTable);

    /// Replaces dashes and output html
    virtual std::string replace(const char pPrev,
                                const char pCur,
                                const char pNext,
                                bool& pConsume);
    
    /// Not used in this replacer
    virtual ReplacerState state() const { return eStateNormal; }

    /// Resets found state
    virtual void reset();

    //// Verifies that found dashes were emitted
    virtual void verify() const;

private:
    /// A dash block of atleast two was found
    int mCount;
};

#endif