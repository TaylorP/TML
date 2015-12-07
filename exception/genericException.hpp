#ifndef GENERIC_EXCEPTION_HPP
#define GENERIC_EXCEPTION_HPP

#include "exception/exception.hpp"

/// Exception for unexpected stream termination
class GenericException : public Exception
{
public:
    GenericException(const std::string& pMessage)
        : mMessage(pMessage)
    {   
    }
    
private:
    /// Generic exception message
    std::string mMessage;

    /// Prints the exception to a stream
    virtual void print(std::ostream& pStream) const
    {
        pStream << mMessage;
    }
};

#endif