#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <iostream>

#include "text/colors.hpp"

/// Generic exception for tokenization and parsing
class Exception
{
public:
    /// Output operator for the exception
    friend std::ostream& operator<<(std::ostream& pStream, const Exception& pException)
    {
        pStream << Colors::red();
        pException.print(pStream);
        pStream << Colors::reset();

        return pStream;
    }

private:
    /// Prints the exception to a stream
    virtual void print(std::ostream& pStream) const = 0;
};

#endif
