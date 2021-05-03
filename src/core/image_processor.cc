#include <core/image_processor.h>

namespace naivebayes {

ImageProcessor::ImageProcessor() = default;

std::vector<Image>& ImageProcessor::GetImages() {
    return images_;
}

std::istream& operator>>(std::istream& is, ImageProcessor& imageProcessor) {
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
}

std::ostream& operator<<(std::ostream& os, ImageProcessor& imageProcessor) {
    for (Image& image : imageProcessor.images_) {
        os << image;
    }
    return os;
}

} // namespace naivebayes

