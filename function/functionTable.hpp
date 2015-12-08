#ifndef FUNCTION_TABLE_HPP
#define FUNCTION_TABLE_HPP

#include <iostream>
#include <unordered_map>

#include "function/function.hpp"

/// Table of supported functions. TODO: Load functions from file definitions
class FunctionTable
{
public:
    /// Constructs a new function table
    FunctionTable(const bool pFilter);

    /// Cleans up the function table
    ~FunctionTable();

    /// Runs a function and writes the contents to a stream
    void emit(std::ostream& pStream,
              const std::string& pName,
              const std::vector<std::string> pParams);

private:
    /// Table for registering functions
    std::unordered_map<std::string, Function*> mTable;
};

#endif