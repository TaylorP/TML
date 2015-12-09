#ifndef PAIR_REPLACER_HPP
#define PAIR_REPLACER_HPP

#include <iostream>

#include "text/replacer/replacer.hpp"

/// Replaces pairs, e.g. *...*, with HTML
class PairReplacer : public Replacer
{
public:
    /// Constructs a new pair replacer
    PairReplacer(const ReplacerTable* pTable,
                 const char pSymbol,
                 const std::string& pLeft,
                 const std::string& pRight,
                 const ReplacerState pState,
                 const bool pCode=false);

    /// Checks for replacement
    virtual std::string replace(const char pPrev,
                                const char pCur,
                                const char pNext,
                                bool& pConsume);

    /// Used to indicate if a code block is active
    virtual ReplacerState state() const;

    /// Resets the pair replacer to the undetected stqate
    virtual void reset();

    /// Verifies that no hanging symbols are left
    virtual void verify() const;

private:
    /// The symbol to replace
    char mSymbol;

    /// The sequence to insert on the left instance
    std::string mLeft;

    /// The sequence to insert on the right instance
    std::string mRight;

    /// The state to return when the replacer is active
    ReplacerState mState;

    /// The current replacement state. false = left, true = right
    bool mSide;

    /// Whether or not the replacment is allowed in code
    bool mCode;
};

#endif