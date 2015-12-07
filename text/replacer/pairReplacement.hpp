#ifndef PAIR_REPLACEMENT_HPP
#define PAIR_REPLACEMENT_HPP

/// Defines a replacement pair for use with the text utlities
class PairReplacement
{
public:
    /// Constructs a new pair replacement instance
    PairReplacement(const std::string& pLeft,
                    const std::string& pRight)
        : mLeft(pLeft),
          mRight(pRight),
          mReplaceState(false)
    {
    }

    /// Resets the pair replacer
    inline void reset()
    {
        mReplaceState = false;
    }

    /// Returns true if the replacement has terminated
    inline bool terminated() const
    {
        return mReplaceState == false;
    }

    /// Returns the replacement and flips the state bit
    inline const std::string& replacement()
    {
        mReplaceState = !mReplaceState;

        if (mReplaceState)
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

    /// The current replacement state. True = left, false = right
    bool mReplaceState;
};

#endif