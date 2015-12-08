#ifndef VIDEO_FUNCTION_HPP
#define VIDEO_FUNCTION_HPP

#include "function/function.hpp"
#include "exception/functionException.hpp"

/// Function for vimeo video blocks
class VideoFunction : public Function
{
public:
    /// Constructs a new latex function
    VideoFunction(const bool pFilter)
        : Function(pFilter)
    {
    }

    /// Emits a video block to the stream
    virtual void emit(std::ostream& pStream,
                      const std::vector<std::string>& pInput) const
    {
        // Validate parameter count
        if (pInput.size() != 3)
        {
            throw(FunctionException("@video",
                                    "Function expects exactly 3 parameter"));
        }

        // Output the centered block
        pStream << "<div class='centered'>";
        newline(pStream);

        pStream << "<iframe src='http://player.vimeo.com/video/" 
                << pInput[0] << "?color=2ecc71' width='"
                << pInput[1] << "' height='"
                << pInput[2] << "' frameborder='0'"
                << " webkitallowfullscreen mozallowfullscreen"
                << " allowfullscreen></iframe>";

        newline(pStream);
        
        pStream << "</div>";
        newline(pStream);
    }
};

#endif
