#include <sstream>

#include "text/replacer/apostropheReplacer.hpp"
#include "text/replacer/dashReplacer.hpp"
#include "text/replacer/pairReplacer.hpp"
#include "text/replacer/replacerTable.hpp"
#include "text/replacer/urlReplacer.hpp"

#include "text/symbols.hpp"

ReplacerTable::ReplacerTable()
{
    // Register built in replacers
    mReplacers.push_back(new ApostropheReplacer());
    mReplacers.push_back(new DashReplacer());
    mReplacers.push_back(new UrlReplacer());

    // Do pair replacement last since it emits HTML
    mReplacers.push_back(new PairReplacer());
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

        // Apply the replacers in order
        bool consume = false;
        std::vector<Replacer*>::iterator itr;
        for(itr = mReplacers.begin(); itr != mReplacers.end(); ++itr)
        {
            std::string result =
                ((Replacer*)(*itr))->replace(previous,
                                             current,
                                             next,
                                             skipNext,
                                             consume);
                
            // Right now we only support one replacer if there's a match
            if (result.length() > 0)
            {
                pOut << result;
                break;
            }
        }

        // Use the regular character
        if (!consume)
        {
            pOut << current;
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