#include "text/replacer/replacerState.hpp"
#include "text/replacer/replacerTable.hpp"
#include "text/replacer/urlReplacer.hpp"
#include "text/symbols.hpp"

UrlReplacer::UrlReplacer(const ReplacerTable* pTable)
    : Replacer(pTable), mState(eLabelEnter), mUseTarget(false)
{
}

std::string UrlReplacer::replace(const char pPrev,
                                 const char pCur,
                                 const char pNext,
                                 bool& pConsume)
{
    if (mTable->state() == eStateCode)
    {
        return "";
    }

    switch (mState)
    {
        case eLabelEnter:
        {
            if (Symbols::isUrlOpen(pCur))
            {
                mState = eLabel;
                pConsume = true;
            }

            break;
        }

        case eLabel:
        {
            pConsume = true;

            if (Symbols::isUrlClosed(pCur))
            {
                mState = eLinkEnter;
            }
            else
            {
                mLabel << pCur;
            }
            break;
        }

        case eLinkEnter:
        {
            pConsume = true;
            mState = eLink;

            if (!Symbols::isOpen(pCur))
            {
                std::cout << "Warning: " << Colors::yellow()
                          << "Invalid symbol in URL, expected ("
                          << " but found `" << pCur << "`. " 
                          << "Attempting to process anyway."
                          << Colors::reset() << std::endl;
            }

            break;
        }

        case eLink:
        {
            pConsume = true;

            if (Symbols::isClosed(pCur) && !Symbols::isClosed(pNext))
            {
                mState = eLabelEnter;
                return emit();
            }
            else if (Symbols::isDelim(pCur))
            {
                mState = eTarget;
                mUseTarget = true;
            }
            else
            {
                mLink << pCur;
            }

            break;
        }

        case eTarget:
        {
            pConsume = true;

            if (Symbols::isSpace(pCur))
            {
                // pass
            }
            else if (Symbols::isClosed(pCur) && !Symbols::isClosed(pNext))
            {
                mState = eLabelEnter;
                return emit();
            }
            else
            {
                mTarget << pCur;
            }
        }

        default:
        {
            break;
        }
    }

    return "";
}

ReplacerState UrlReplacer::state() const
{
    if (mState != eLabelEnter)
    {
        return eStateUrl;
    }

    return eStateNormal;
}

void UrlReplacer::reset()
{
    mState = eLabelEnter;
    mUseTarget = false;
    mLabel.str("");
    mLink.str("");
    mTarget.str("");
}

void UrlReplacer::verify() const
{
    if (mState != eLabelEnter)
    {
        std::cout << "Warning: " << Colors::yellow()
                  << "url replacer did not terminated cleanly. " << std::endl
                  << "Label buffer contains: " << mLabel.str() << std::endl
                  << "Link buffer contains: " << mLink.str() << Colors::reset()
                  << std::endl;
    }
}

std::string UrlReplacer::emit()
{
    std::stringstream urlString;
    
    urlString << "<a href='" << mLink.str() << "'";
    if (mUseTarget)
    {
        urlString << "target='_" << mTarget.str() << "'";
    }
    urlString << ">" << mLabel.str() << "</a>";

    reset();

    return urlString.str();
}