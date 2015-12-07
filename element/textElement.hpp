#ifndef TEXT_ELEMENT_HPP
#define TEXT_ELEMENT_HPP

#include <string>

#include "element/element.hpp"

/// Plain text element
class TextElement : public Element
{
public:
    /// Constructs a new text element
    TextElement();

    /// Returns the text stored on the element
    inline const std::string& text() const
    {
        return mText;
    }

private:
    /// The text data
    std::string mText;

    /// Parses an element from an input stream
    virtual void parse(std::istream& pStream);

    /// Prints the text element to the stream
    virtual void print(std::ostream& pStream) const;
};

#endif