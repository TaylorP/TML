#ifndef PAIR_REPLACEMENT_HPP
#define PAIR_REPLACEMENT_HPP

#include "text/replacer/replacerState.hpp"

/// Defines a replacement pair for use with the text utlities
class PairReplacement
{
public:
    /// Constructs a new pair replacement instance
    PairReplacement(const std::string& pLeft,
                    const std::string& pRight,
                    const ReplacerState pState)
        : mLeft(pLeft),
          mRight(pRight),
          mState(pState),
          mSide(false)
    {
    }

    /// Resets the pair replacer
    inline void reset()
    {
        mSide = false;
    }

    /// Returns true if the replacement has terminated
    inline bool terminated() const
    {
        return mSide == false;
    }

    /// Returns the state of the replacement
    inline ReplacerState state() const
    {
        if (mSide)
        {
            return mState;
        }

        return eStateNormal;
    }

    /// Returns the replacement and flips the state bit
    inline const std::string& replacement()
    {
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

private:
    /// The sequence to insert on the left instance
    std::string mLeft;

    /// The sequence to insert on the right instance
    std::string mRight;

    /// The state to return when the replacer is active
    ReplacerState mState;

    /// The current replacement state. false = left, true = right
    bool mSide;
};

#endif