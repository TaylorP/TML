#include <fstream>
#include <iostream>

#include "exception/exception.hpp"
#include "parser/parser.hpp"

int main(int argc, char** argv)
{
    if (argc == 2 || argc == 3)
    {
        try
        {
            Parser parser;

            std::ifstream in;
            in.open(argv[1], std::ios::in);

            if (argc == 3)
            {
                std::ofstream fout;
                fout.open(argv[2], std::ios::out);
                parser.parse(fout, in);
            }
            else
            {
                parser.parse(std::cout, in);
            }
        }
        catch (const Exception& e)
        {
            std::cout << "Error: " << e << std::endl;
            return 1;
        }
    }
    else
    {
        std::cout << "Usage: tml_parse <input-file> [output-file]"
                  << std::endl;
    }

    return 0;
}