#ifndef FUNCTION_EXCEPTION_HPP
#define FUNCTION_EXCEPTION_HPP

#include <string>
#include "exception.hpp"

/// Function processing exception
class FunctionException : public Exception
{
public:
    /// Constructs a new function exception
    FunctionException(const std::string& pFunction,
                      const std::string& pError)
        : mFunction(pFunction),
          mError(pError)
    {
    }

private:
    /// The function name
    std::string mFunction;

    /// The error message
    std::string mError;

    /// Prints the exception to a stream
    virtual void print(std::ostream& pStream) const
    {
        pStream << "Error evaluating function `" << mFunction
                << "`" << std::endl;
        pStream << "\t" << mError;
    }
};

#endif