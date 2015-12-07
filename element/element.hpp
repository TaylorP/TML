#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <iostream>
#include <sstream>

/// Abstract base class for parsed elements
class Element
{
public:
    /// Input stream operator
    friend std::istream& operator>>(std::istream& pStream, Element& pElement)
    {
        pElement.parse(pStream);
        return pStream;
    }

    /// Output operator
    friend std::ostream& operator<<(std::ostream& pStream, const Element& pElement)
    {
        pElement.print(pStream);
        return pStream;
    }
    
private:
    /// Parses an element from an input stream
    virtual void parse(std::istream& pStream) = 0;

    /// Prints the element to the given stream, for output purposes
    virtual void print(std::ostream& pStream) const = 0;
};

#endif