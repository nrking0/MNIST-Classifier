#ifndef NAIVE_BAYES_IMAGE_PROCESSOR_H
#define NAIVE_BAYES_IMAGE_PROCESSOR_H

#include <iostream>
#include <core/image.h>

namespace naivebayes {

/** Class used to take in a file and process it into images. */
class ImageProcessor {

public:
    /** Basic constructor for set up. */
    ImageProcessor();

    std::vector<Image>& GetImages();

    /**
     * Overload for the input operator to take in a file and process it into a vector of images.
     *
     * @param is input stream, in this case a file
     * @param imageProcessor the image processor that will receive the data
     * @return the input stream after finished
     */
    friend std::istream& operator>>(std::istream& is, ImageProcessor& imageProcessor);

    /**
     * Simple overload of output operator to display all images in console.
     *
     * @param os output stream
     * @param imageProcessor the image processor whose images are to be displayed
     * @return the output stream after finished
     */
    friend std::ostream& operator<<(std::ostream& os, ImageProcessor& imageProcessor);

private:
    std::vector<Image> images_;
};


} // namespace naivebayes

#endif //NAIVE_BAYES_IMAGE_PROCESSOR_H
