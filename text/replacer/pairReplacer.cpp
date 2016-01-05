#include "text/replacer/pairReplacer.hpp"
#include "text/replacer/replacerTable.hpp"
#include "text/colors.hpp"
#include "text/symbols.hpp"

PairReplacer::PairReplacer(const ReplacerTable* pTable,
                           const char pSymbol,
                           const std::string& pLeft,
                           const std::string& pRight,
                           const ReplacerState pState,
                           const bool pCode)
    : Replacer(pTable),
      mSymbol(pSymbol),
      mLeft(pLeft),
      mRight(pRight),
      mState(pState),
      mCode(pCode)
{
}

std::string PairReplacer::replace(const char pPrev,
                                  const char pCur,
                                  const char pNext,
                                  bool& pConsume)
{
    if (mTable->state() == eStateUrl ||
        mTable->state() == eStateNumeric || 
        (mTable->state() == eStateCode && !mCode))
    {
        return "";
    }

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