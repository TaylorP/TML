#include "text/replacer/pairReplacer.hpp"
#include "text/colors.hpp"
#include "text/symbols.hpp"

PairReplacer::PairReplacer(const ReplacerTable* pTable,
                           const char pSymbol,
                           const std::string& pLeft,
                           const std::string& pRight,
                           const ReplacerState pState)
    : Replacer(pTable),
      mSymbol(pSymbol),
      mLeft(pLeft),
      mRight(pRight),
      mState(pState)
{
}

std::string PairReplacer::replace(const char pPrev,
                                  const char pCur,
                                  const char pNext,
                                  bool& pConsume)
{
    // Return the replacement if one is found
    if (pCur == mSymbol)
    {
        pConsume = true;
        mSide = !mSide;

        if (mSide)
        {
            return mLeft;
        }
        else
        {
            return mRight;
        }
    }

    return "";
}

ReplacerState PairReplacer::state() const
{
    if (mSide)
    {
        return mState;
    }

    return eStateNormal;
}

void PairReplacer::reset()
{
    mSide = false;
}

void PairReplacer::verify() const
{
    if (mSide)
    {
            std::cout << "Warning: " << Colors::yellow() << "pair replacer for "
                      << mSymbol << " did not terminate."
                      << " Potential hanging symbol?" << Colors::reset()
                      << std::endl;
    }
}