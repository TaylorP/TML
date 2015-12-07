#include "function/codeFunction.hpp"
#include "function/functionTable.hpp"
#include "function/headerFunction.hpp"
#include "function/imageFunction.hpp"
#include "function/latexFunction.hpp"
#include "function/textFunction.hpp"

FunctionTable::FunctionTable()
{
    // Register built-in functions
    mTable["code"] = new CodeFunction();
    mTable["header"] = new HeaderFunction();
    mTable["image"] = new ImageFunction();
    mTable["latex"] = new LatexFunction();
    mTable["text"] = new TextFunction();
}

FunctionTable::~FunctionTable()
{
    // Delete built in functions
    std::unordered_map<std::string, Function*>::iterator itr;
    for(itr = mTable.begin(); itr != mTable.end(); itr++)
    {
        delete itr->second;
    }
}

void FunctionTable::emit(std::ostream& pStream,
                         const std::string& pName,
                         const std::vector<std::string> pParams)
{
    // Find the function in the table
    if (mTable.count(pName) > 0)
    {
        mTable[pName]->emit(pStream, pParams);
    }
    // Function wasn't found, so throw an exception
    else
    {
        throw(FunctionException(pName, "Function not found."));
    }
}