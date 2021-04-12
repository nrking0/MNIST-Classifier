#include <core/classifier.h>

namespace naivebayes {

Classifier::Classifier() = default;

void Classifier::ClassifyImageSet(ImageProcessor &imageProcessor, Model& model) {
    std::vector<Image>& images = imageProcessor.GetImages();

    for (Image& image : images) {
        double max_probability = 0.0;
        int max_index = -1;

        for (size_t i = 0; i < 10; i++) {
            double probability = model.GetProbClassC()[i];

            for (size_t row = 0; row < image.GetSize(); row++) {

                for (size_t col = 0; col < image.GetSize(); col++) {
                    probability = probability * model.GetProbPixelValues()[row][col][i][image.GetPixelShade(row, col)];
                }
            }

            if (probability > max_probability) {
                max_probability = probability;
                max_index = i;
            }
        }
        image.SetClassification(max_index);
    }
}

double Classifier::ValidateImageSetClassification(ImageProcessor &imageProcessor) {
    int image_count = 0;
    int correct_classification_count = 0;

    for (const Image& image : imageProcessor.GetImages()) {
        if (image.GetValue() == image.GetClassification()) {
            image_count++;
            correct_classification_count++;
        } else {
            image_count ++;
        }
    }

    return (1.0 * correct_classification_count / image_count);
}

} // namespace naivebayes

