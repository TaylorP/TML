#ifndef IMAGE_FUNCTION_HPP
#define IMAGE_FUNCTION_HPP

#include "function/function.hpp"
#include "exception/functionException.hpp"

/// Function for full width blocks with 1 or more images
class ImageFunction : public Function
{
public:
    /// Emits an image block to the stream
    virtual void emit(std::ostream& pStream,
                      const std::vector<std::string>& pInput) const
    {
        // Validate parameter count
        if (pInput.size() < 2)
        {
            throw(FunctionException("@image",
                                    "Function expects 2 or more parameters"));
        }

        // Only use annotation syntax if the annotation is non-empty
        bool annotated = (pInput[0].length() != 0);

        // Print the centering block
        pStream << "<div class='centered'>" << std::endl;

        // Print the annotation container if needed
        if (annotated)
        {
            pStream << "<div class ='annotated-images'>" << std::endl;
        }

        // Print the images
        for (int i = 1; i < pInput.size(); i++)
        {
            pStream << "<img src='" << pInput[i] << "'/>" << std::endl;
        }

        // Add the annotation and close the annotation header
        if (annotated)
        {
            pStream << "<p>" << pInput[0] << "</p>" << std::endl;
            pStream << "</div>" << std::endl;
        }

        // Close the center block
        pStream << "</div>" << std::endl;
    }
};

#endif
