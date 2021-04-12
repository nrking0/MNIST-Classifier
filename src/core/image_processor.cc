#include <core/image_processor.h>

namespace naivebayes {

ImageProcessor::ImageProcessor() = default;

const std::vector<Image> & ImageProcessor::GetImages() const {
    return images_;
}

} // namespace naivebayes

