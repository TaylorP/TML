#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "exception/exception.hpp"
#include "parser/parser.hpp"

int main(int argc, char** argv)
{
    if (argc > 2)
    {
        std::ifstream fin;
        fin.open(argv[1], std::ios::in);

        std::ofstream fout;
        fout.open(argv[2], std::ios::out);

        try
        {
            Parser parser;
            parser.parse(fout, fin);
        }
        catch (const Exception& e)
        {
            std::cout << "Error: " << e << std::endl;
            return 1;
        }
    }

    return 0;
}