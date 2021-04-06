#include <core/image_processor.h>

namespace naivebayes {

    ImageProcessor::ImageProcessor() {}

    const std::vector<Image> & ImageProcessor::GetImages() const {
        return images_;
    }

    void ImageProcessor::display() const {
        for (Image i : images_) {
            i.display();
        }
    }
} // namespace naivebayes

