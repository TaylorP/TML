#ifndef URL_REPLACER_HPP
#define URL_REPLACER_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

#include "text/replacer/replacer.hpp"

/// Replaces markdown style urls, e.g (label)[link]
class UrlReplacer : public Replacer
{
public:
    /// Constructs a new url replacer
    UrlReplacer(const ReplacerTable* pTable);

    /// Replaces dashes and output html
    virtual std::string replace(const char pPrev,
                                const char pCur,
                                const char pNext,
                                bool& pConsume);
    
    /// Returns the URL state if the parser is not in the resting state
    virtual ReplacerState state() const;

    /// Resets found state
    virtual void reset();

    //// Verifies that found dashes were emitted
    virtual void verify() const;

private:
    /// Emits a url string
    std::string emit();

    /// Replacer states
    enum State
    {
        eResting,
        eLabelEnter,
        eLabel,
        eLinkEnter,
        eLink,
        eTarget
    };

    /// The current state
    State mState;

    /// Whether or not the link should open in a target
    bool mUseTarget;

    /// Url label string accumulator
    std::stringstream mLabel;

    /// Url link string accumulator
    std::stringstream mLink;

    /// The target for the Url
    std::stringstream mTarget;
};

#endif