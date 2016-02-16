#include "function/codeFunction.hpp"
#include "function/contentsFunction.hpp"
#include "function/functionTable.hpp"
#include "function/headerFunction.hpp"
#include "function/imageFunction.hpp"
#include "function/latexFunction.hpp"
#include "function/subheaderFunction.hpp"
#include "function/textFunction.hpp"
#include "function/videoFunction.hpp"

FunctionTable::FunctionTable(const bool pFilter)
{
    // Register built-in functions
    mTable["code"] = new CodeFunction(pFilter);
    mTable["contents"] = new ContentsFunction(pFilter);
    mTable["header"] = new HeaderFunction(pFilter);
    mTable["subheader"] = new SubheaderFunction(pFilter);
    mTable["image"] = new ImageFunction(pFilter);
    mTable["latex"] = new LatexFunction(pFilter);
    mTable["text"] = new TextFunction(pFilter);
    mTable["video"] = new VideoFunction(pFilter);
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
