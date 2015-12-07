#ifndef COLORS_HPP
#define COLORS_HPP

/// Utility for setting output color via escape codes
namespace Colors
{
    /// Returns the color reset sequence
    static inline const char* reset()
    {
        return "\033[0m";
    }

    /// Returns the red color start sequence
    static inline const char* red()
    {
        return "\033[1;31m";
    }

    /// Returns the green color start sequence
    static inline const char* green()
    {
        return "\033[1;32m";
    }

    /// Returns the yellow color start sequence
    static inline const char* yellow()
    {
        return "\033[1;33m";
    }
}

#endif