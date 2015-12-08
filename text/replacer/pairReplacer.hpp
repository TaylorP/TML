#ifndef PAIR_REPLACER_HPP
#define PAIR_REPLACER_HPP

#include <iostream>
#include <unordered_map>

#include "text/replacer/pairReplacement.hpp"
#include "text/replacer/replacer.hpp"

/// Replaces registered pairs of symbols, e.g. *aaaa* or _test_, with
/// the proper HTML output
class PairReplacer : public Replacer
{
public:
    /// Constructs a new pair replacer
    PairReplacer(const ReplacerTable* pTable);

    /// Destroys a pair replacer
    ~PairReplacer();

    /// Runs all pair replacers on the given input
    virtual std::string replace(const char pPrev,
                                const char pCur,
                                const char pNext,
                                bool& pConsume);

    /// Used to indicate if a code block is active
    virtual ReplacerState state() const;

    /// Resets the pair replacements
    virtual void reset();

    /// Verifies that the replacements all completed
    virtual void verify() const;

private:
    /// The list of replacements to perform
    std::unordered_map<char, PairReplacement*> mReplacements;
};

#endif