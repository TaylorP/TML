#include <sstream>

#include "text/replacer/apostropheReplacer.hpp"
#include "text/replacer/dashReplacer.hpp"
#include "text/replacer/pairReplacer.hpp"
#include "text/replacer/replacerTable.hpp"
#include "text/replacer/urlReplacer.hpp"

#include "text/symbols.hpp"

ReplacerTable::ReplacerTable(const bool pFilter)
    : mFilter(pFilter)
{
    mReplacers.push_back(new ApostropheReplacer(this));
    mReplacers.push_back(new DashReplacer(this));
    mReplacers.push_back(new UrlReplacer(this));

    mReplacers.push_back(
        new PairReplacer(this, '\'', "&#8216;", "&#8217;", eStateNormal));
    mReplacers.push_back(
        new PairReplacer(this, '"', "&#8220;", "&#8221;", eStateNormal));

    mReplacers.push_back(
        new PairReplacer(this, '^', "<sup>", "</sup>", eStateNormal));

    mReplacers.push_back(
        new PairReplacer(this, '*', "<b>", "</b>", eStateNormal));
    mReplacers.push_back(
        new PairReplacer(this, '_', "<i>", "</i>", eStateNormal));
    mReplacers.push_back(
        new PairReplacer(this, '%',"<span class='number'>",
                         "</span>", eStateNormal));
    mReplacers.push_back(
        new PairReplacer(this, '`', "<span class=\'inline-code\'>",
                         "</span>", eStateCode, true));
}

ReplacerTable::~ReplacerTable()
{
    // Delete replacer objects
    std::vector<Replacer*>::iterator itr;
    for(itr = mReplacers.begin(); itr != mReplacers.end(); ++itr)
    {
        delete *itr;
    }
}

void ReplacerTable::replace(std::ostream& pOut, std::istream& pIn)
{
    // Reset all replacemers
    reset();

    bool skipNext = false;
    char previous = 0;

    // Loop over all the characters
    while (true)
    {
        // Abort once EOF is reached
        int i = pIn.get();
        if (pIn.eof())
        {
            break;
        }

        char current = (char)(i);
        char next = (char)(pIn.peek());

        // If the character is a \ do escape handling
        if (Symbols::isEscape(current))
        {
            // If the preceding character was a \ we want to
            // keep the current \, so  check the escape flag here
            if (!skipNext)
            {
                // Discard the \ but mark the next character as
                // escaped
                skipNext = true;
                continue;
            }
        }

        bool consume = false;

        if (!skipNext)
        {
            // Apply the replacers in order
            std::vector<Replacer*>::iterator itr;
            for(itr = mReplacers.begin(); itr != mReplacers.end(); ++itr)
            {
                std::string result =
                    ((Replacer*)(*itr))->replace(previous,
                                                 current,
                                                 next,
                                                 consume);
                    
                // Right now we only support one replacer if there's a match
                if (result.length() > 0)
                {
                    pOut << result;
                    break;
                }
            }
        }

        // Use the regular character
        if (!consume)
        {
            if (!mFilter || !Symbols::isNewline(current))
            {
                pOut << current;
            }
        }

        // Clear the escape flag
        skipNext = false;
        previous = current;
    }

    // Verify termination on all replacemers
    verify();
}

void ReplacerTable::replace(std::ostream& pOut, const std::string& pString)
{
    std::stringstream stream(pString);
    replace(pOut, stream);
}

ReplacerState ReplacerTable::state() const
{
    std::vector<Replacer*>::const_iterator itr;
    for(itr = mReplacers.begin(); itr != mReplacers.end(); ++itr)
    {
        ReplacerState state = ((Replacer*)(*itr))->state();
        if (state != eStateNormal)
        {
            return state;
        }
    }

    return eStateNormal;
}

void ReplacerTable::reset()
{
    std::vector<Replacer*>::iterator itr;
    for(itr = mReplacers.begin(); itr != mReplacers.end(); ++itr)
    {
        ((Replacer*)(*itr))->reset();
    }
}

void ReplacerTable::verify() const
{
    std::vector<Replacer*>::const_iterator itr;
    for(itr = mReplacers.begin(); itr != mReplacers.end(); ++itr)
    {
        ((Replacer*)(*itr))->verify();
    }
}