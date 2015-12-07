#include "text/replacer/dashReplacer.hpp"
#include "text/symbols.hpp"

DashReplacer::DashReplacer()
    : mCount(0)
{
}

std::string DashReplacer::replace(const char pPrev,
                                  const char pCur,
                                  const char pNext,
                                  const bool pSkip,
                                  bool& pConsume)
{
    // Print the replacement or regular output
    if (Symbols::isHyphen(pCur) && !pSkip)
    {
        // Next symbol is also a hyphen, so start a multi-dash
        if (Symbols::isHyphen(pNext))
        {
            pConsume = true;
            mCount++;
            return "";
        }
        // 2 dashes recorded. Emit an en-dash
        else if (mCount == 1)
        {
            pConsume = true;
            mCount = 0;
            return "&#8211;";
        }
        // 3 dashes recorded. Emit an em-dash
        else if (mCount == 2)
        {
            pConsume = true;
            mCount = 0;
            return "&#8212;";
        }
    }

    return "";
}

void DashReplacer::reset()
{
    mCount = 0;
}

void DashReplacer::verify() const
{
    if (mCount != 0)
    {
        std::cout << "Warning: " << Colors::yellow()
                  << "dash replacer did not terminated cleanly. "
                  << "Potential hanging symbol?" << Colors::reset()
                  << std::endl;
    }
}