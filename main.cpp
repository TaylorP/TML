#include <fstream>
#include <iostream>

#include "exception/exception.hpp"
#include "parser/parser.hpp"

void usageError()
{
    std::cout << "Usage: tml_parse [-f] [-o <output-file>] <input-file>"
              << std::endl;
}

void argError(std::string& pArg)
{
    std::cout << "Invalid argument `" << pArg << "`" << std::endl;
}

void outputError(std::string& pOutput, bool missing=false)
{
    if (missing)
    {
        std::cout << "Missing output file after -o" << std::endl;
    }
    else
    {
        std::cout << "Invalid or inaccessebile output file `"
                  << pOutput << "`" << std::endl;
    }
}

int main(int argc, char** argv)
{
    std::string input = "input.tml";
    std::string output = "out.html";
    bool filter = false;

    for (int i = 1; i < argc; i++)
    {
        std::string arg(argv[i]);
        if (arg[0] == '-')
        {
            if (arg.length() < 2)
            {
                argError(arg);
                return 0;
            }
            else if (arg[1] == 'f')
            {
                filter = true;
            }
            else if (arg[1] == 'o')
            {
                if (i < argc - 1)
                {
                    output = std::string(argv[i+1]);
                }
                else
                {
                    outputError(output, true);
                }
            }
            else
            {
                argError(arg);
                return 0;
            }

            continue;
        }

        input = arg;
    }

    if (input.length() == 0)
    {
        usageError();
        return 0;
    }

    std::ifstream in;
    in.open(input, std::ios::in);

    std::ofstream out;
    out.open(output, std::ios::out);
    if (!out.is_open())
    {
        outputError(output);
        return 0;
    }

    try
    {
        Parser parser(filter);
        parser.parse(out, in);
    }
    catch (const Exception& e)
    {
        std::cout << "Error: " << e << std::endl;
    }

    in.close();
    out.close();

    return 0;
}