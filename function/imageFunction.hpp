#ifndef IMAGE_FUNCTION_HPP
#define IMAGE_FUNCTION_HPP

#include "function/function.hpp"
#include "exception/functionException.hpp"

/// Function for full width blocks with 1 or more images
class ImageFunction : public Function
{
public:
    /// Constructs a new image function
    ImageFunction(const bool pFilter)
        : Function(pFilter)
    {
    }

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
        pStream << "<div class='centered'>";
        newline(pStream);

        // Print the annotation container if needed
        if (annotated)
        {
            pStream << "<div class ='annotated-images'>";
            newline(pStream);
        }

        // Print the images
        for (int i = 1; i < pInput.size(); i+=2)
        {
            if (i == pInput.size() - 1)
            {
                throw(FunctionException("@image",
                                        "Function expects alt tag for each image"));
            }

            pStream << "<img src='" << pInput[i]
                    << "' alt='" << pInput[i+1] << "'/>";
            newline(pStream);
        }

        // Add the annotation and close the annotation header
        if (annotated)
        {
            pStream << "<p>" << pInput[0] << "</p>";
            newline(pStream);

            pStream << "</div>";
            newline(pStream);
        }

        // Close the center block
        pStream << "</div>";
        newline(pStream);
    }
};

#endif
