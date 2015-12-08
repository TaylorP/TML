#include "text/replacer/pairReplacer.hpp"
#include "text/colors.hpp"
#include "text/symbols.hpp"

PairReplacer::PairReplacer(const ReplacerTable* pTable)
    : Replacer(pTable)
{
    // Style replacements
    mReplacements['*'] =
        new PairReplacement("<b>", "</b>", eStateNormal);
    mReplacements['_'] =
        new PairReplacement("<i>", "</i>",  eStateNormal);
    mReplacements['`'] =
        new PairReplacement("<span class=\'inline-code\'>",
                            "</span>",
                            eStateCode);

    // Single quote replacements
    mReplacements['\''] =
        new PairReplacement("&#8216;", "&#8217;", eStateNormal);

    // Double quote replacements
    mReplacements['"'] =
        new PairReplacement("&#8220;", "&#8221;", eStateNormal);
}

PairReplacer::~PairReplacer()
{
    // Delete built in functions
    std::unordered_map<char, PairReplacement*>::iterator itr;
    for(itr = mReplacements.begin(); itr != mReplacements.end(); itr++)
    {
        delete itr->second;
    }
}

std::string PairReplacer::replace(const char pPrev,
                                  const char pCur,
                                  const char pNext,
                                  bool& pConsume)
{
    // Return the replacement if one is found
    if (mReplacements.count(pCur) > 0)
    {
        pConsume = true;
        return mReplacements[pCur]->replacement();
    }

    return "";
}

ReplacerState PairReplacer::state() const
{
    // Reset all replacements to their default
    std::unordered_map<char, PairReplacement*>::const_iterator itr;
    for(itr = mReplacements.begin(); itr != mReplacements.end(); itr++)
    {
        ReplacerState state = ((PairReplacement*)itr->second)->state();
        if (state != eStateNormal)
        {
            return state;
        }
    }

    return eStateNormal;
}

void PairReplacer::reset()
{
    // Reset all replacements to their default
    std::unordered_map<char, PairReplacement*>::iterator itr;
    for(itr = mReplacements.begin(); itr != mReplacements.end(); itr++)
    {
        ((PairReplacement*)itr->second)->reset();
    } 
}

void PairReplacer::verify() const
{
    // Print a warning message if any of the replacements failed to be closed
    // properly
    std::unordered_map<char, PairReplacement*>::const_iterator itr;
    for(itr = mReplacements.begin(); itr != mReplacements.end(); itr++)
    {
        if (!((PairReplacement*)itr->second)->terminated())
        {
            std::cout << "Warning: " << Colors::yellow() << "pair replacer for "
                      << itr->first << " did not terminate."
                      << " Potential hanging symbol?" << Colors::reset()
                      << std::endl;
        }
    } 
}