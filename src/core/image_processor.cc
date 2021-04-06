#include <core/image_processor.h>

namespace naivebayes {

    ImageProcessor::ImageProcessor() = default;

    const std::vector<Image> & ImageProcessor::GetImages() const {
        return images_;
    }

    void ImageProcessor::display() const {
        for (const Image& image : images_) {
            image.display();
        }
    }
} // namespace naivebayes

