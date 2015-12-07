#ifndef EOF_EXCEPTION_HPP
#define EOF_EXCEPTION_HPP

#include "exception/exception.hpp"

/// Exception for unexpected stream termination
class EOFException : public Exception
{
private:
    /// Prints the exception to a stream
    virtual void print(std::ostream& pStream) const
    {
        pStream << "Unexpected end of file (EOF) reached.";
    }
};

#endif