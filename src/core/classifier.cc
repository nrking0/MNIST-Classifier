#include <core/classifier.h>
#include <limits>

namespace naivebayes {

Classifier::Classifier(const Model& model) {
    model_ = model;
};

void Classifier::ClassifyImageSet(ImageProcessor &imageProcessor) {
    std::vector<Image>& images = imageProcessor.GetImages();

    for (Image& image : images) {
        double max_probability = -std::numeric_limits<double>::max();
        int max_index = -1;

        for (size_t i = 0; i < 10; i++) {
            // Starts off with the overall probability of each class
            double probability = log(model_.GetProbClassC()[i]);

            for (size_t row = 0; row < image.GetSize(); row++) {

                for (size_t col = 0; col < image.GetSize(); col++) {
                    // Adds in each individual pixel probability based on conditions
                    probability += log(model_.GetProbPixelValues()[row][col][i][image.GetPixelShade(row, col)]);
                }
            }

            // Checking to see if the latest class is more likely than prior probabilities
            if (probability > max_probability) {
                max_probability = probability;
                max_index = i;
            }
        }
        image.SetClassification(max_index);
    }
}

std::vector<double> Classifier::ClassifyImage(Image &image) {
    std::vector<double> probabilities;
    double max_probability = -std::numeric_limits<double>::max();
    int max_index = -1;

    for (size_t i = 0; i < 10; i++) {
        // Starts off with the overall probability of each class
        double probability = log(model_.GetProbClassC()[i]);

        for (size_t row = 0; row < image.GetSize(); row++) {

            for (size_t col = 0; col < image.GetSize(); col++) {
                // Adds in each individual pixel probability based on conditions
                probability += log(model_.GetProbPixelValues()[row][col][i][image.GetPixelShade(row, col)]);
            }
        }

        probabilities.push_back(probability);
        // Checking to see if the latest class is more likely than prior probabilities
        if (probability > max_probability) {
            max_probability = probability;
            max_index = i;
        }
    }
    image.SetClassification(max_index);
    // Returns vector of all likelihoods for testing purposes
    return probabilities;
}

double Classifier::ValidateImageSetClassification(ImageProcessor &imageProcessor) {
    int image_count = 0;
    int correct_classification_count = 0;

    for (const Image& image : imageProcessor.GetImages()) {

        // Simply iterates through each image and checks to see
        // if it was correctly classified
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

