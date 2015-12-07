#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include <ctype.h>
#include <cstdio>
#include <iostream>

#include "exception/eofException.hpp"

/// Utility methods for symbol comparsion while parsing
namespace Symbols
{
    /// Returns true if the symbol is a valid letter
    static inline bool isLetter(const int pSymbol)
    {
        return isalpha(pSymbol);
    }

    /// Returns true if the symbol is whitespace
    static inline bool isSpace(const int pSymbol)
    {
        return isspace(pSymbol);
    }

    /// Returns true if the symbol is an escape character
    static inline bool isEscape(const int pSymbol)
    {
        return pSymbol == '\\';
    }

    /// Returns true if the symbol is a function call
    static inline bool isFunc(const int pSymbol)
    {
        return pSymbol == '@';
    }

    /// Returns true if the symbol is a delimiter
    static inline bool isDelim(const int pSymbol)
    {
        return pSymbol == ',';
    }

    /// Returns true if the symbol is an open paranthesis
    static inline bool isOpen(const int pSymbol)
    {
        return pSymbol == '(';
    }

    /// Returns true if the symbol is a closed paranthesis
    static inline bool isClosed(const int pSymbol)
    {
        return pSymbol == ')';
    }

    /// Returns true if the symbol is an open square bracket
    static inline bool isUrlOpen(const int pSymbol)
    {
        return pSymbol == '[';
    }

    /// Returns true if the symbol is a closed square bracket
    static inline bool isUrlClosed(const int pSymbol)
    {
        return pSymbol == ']';
    }

    /// Returns true if the symbol is a string quote
    static inline bool isQuote(const int pSymbol)
    {
        return pSymbol == '\'';
    }

    /// Returns true if the symbol is an apostrophe
    static inline bool isApos(const int pSymbol)
    {
        return pSymbol == '\'';
    }

    /// Returns true if the symbol is a hyphen
    static inline bool isHyphen(const int pSymbol)
    {
        return pSymbol == '-';
    }

    /// Returns true if the symbol is a newline
    static inline bool isNewline(const int pSymbol)
    {
        return pSymbol == '\n';
    }

    /// Reads an input symbol from a stream and throws an exception
    /// if no symbol is found
    static inline int readSymbol(std::istream& pStream, bool except=true)
    {
        if (pStream.peek() == EOF)
        {
            if (except)
            {
                throw(EOFException());
            }
        }

        return pStream.get();
    }
}

#endif