#ifndef APOSTROPHE_REPLACER_HPP
#define APOSTROPHE_REPLACER_HPP

#include <iostream>
#include <unordered_map>

#include "text/replacer/replacer.hpp"

/// Replaces apostrophes with the appropriate closing single quote
/// glyph
class ApostropheReplacer : public Replacer
{
public:
    /// Constructs a new replacer
    ApostropheReplacer(const ReplacerTable* pTable)
        : Replacer(pTable)
    {
    }

    /// Replaces apostrophes, e.g `isn't` and `its'` with HTML
    virtual std::string replace(const char pPrev,
                                const char pCur,
                                const char pNext,
                                const bool pSkip,
                                bool& pConsume);
    
    /// Not used in this replacer
    virtual ReplacerState state() const { return eStateNormal; }

    /// Not used in this replacer
    virtual void reset() {}

    /// Not used in this replacer
    virtual void verify() const {}
};

#endif