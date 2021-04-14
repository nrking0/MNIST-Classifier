#ifndef NAIVE_BAYES_CLASSIFIER_H
#define NAIVE_BAYES_CLASSIFIER_H

#include <core/image.h>
#include <core/image_processor.h>
#include <core/model.h>

namespace naivebayes {

class Classifier {

public:
    /**
     * Basic set up constructor for classifier.
     *
     * @param model the model that will be used to classify images.
     */
    explicit Classifier(const Model& model);

    /**
     * Will classify an entire set up images using the model of this classifier.
     *
     * @param imageProcessor image processor that has taken in a set of images
     */
    void ClassifyImageSet(ImageProcessor& imageProcessor);

    /**
     * Will classify an individual image, most useful for individual classifications
     * with the sketchpad.
     *
     * @param image the image to be classified
     * @return a vector of doubles that is the probability scores of each possible value, made
     * accessible for testing of algorithm.
     */
    std::vector<double> ClassifyImage(Image& image);

    /**
     * Validates image set classifications to actual values.
     *
     * @param imageProcessor a set of images that have been classified
     * @return the accuracy ratio of the classifiers success rate
     */
    static double ValidateImageSetClassification(ImageProcessor& imageProcessor);

private:
    Model model_;
};

}

#endif //NAIVE_BAYES_CLASSIFIER_H
