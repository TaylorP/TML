#include "text/replacer/apostropheReplacer.hpp"
#include "text/symbols.hpp"

std::string ApostropheReplacer::replace(const char pPrev,
                                        const char pCur,
                                        const char pNext,
                                        bool& pConsume)
{
    // Print the replacement or regular output
    if (Symbols::isApos(pCur))
    {
        if (Symbols::isLetter(pPrev) && Symbols::isLetter(pNext) ||
            pPrev == 's' && !Symbols::isLetter(pNext))
        {
            pConsume = true;
            return "&#8217;";
        }
    }

    return "";
}