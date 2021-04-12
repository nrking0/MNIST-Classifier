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

    const std::vector<Image>& GetImages() const;

    /**
     * Overload for the input operator to take in a file and process it into a vector of images.
     *
     * @param is input stream, in this case a file
     * @param imageProcessor the image processor that will receive the data
     * @return the input stream after finished
     */
    friend std::istream& operator>>(std::istream& is, ImageProcessor& imageProcessor) {
        std::string curr_line;
        while (std::getline(is, curr_line)) {
            // Checking to see if the line is just a number representing a new image
            if (std::isdigit(curr_line[0])) {
                Image image = Image(std::stoi(curr_line));
                imageProcessor.images_.push_back(image);
            } else {
                // Adding image row to latest image
                std::vector<int> image_row;
                for (char pixel : curr_line) {
                    if (pixel == ' ') {
                        image_row.push_back(0);
                    } else {
                        image_row.push_back(1);
                    }
                }
                size_t size = imageProcessor.images_.size() - 1;
                imageProcessor.images_[size].AddPixelRow(image_row);
            }
        }
        return is;
    };

    /**
     * Simple overload of output operator to display all images in console.
     *
     * @param os output stream
     * @param imageProcessor the image processor whose images are to be displayed
     * @return the output stream after finished
     */
    friend std::ostream& operator<<(std::ostream& os, ImageProcessor& imageProcessor) {
        for (Image& image : imageProcessor.images_) {
            os << image;
        }
        return os;
    };

private:
    std::vector<Image> images_;
};


} // namespace naivebayes

#endif //NAIVE_BAYES_IMAGE_PROCESSOR_H
