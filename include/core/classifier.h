#ifndef NAIVE_BAYES_CLASSIFIER_H
#define NAIVE_BAYES_CLASSIFIER_H

#include <core/image.h>
#include <core/image_processor.h>
#include <core/model.h>

namespace naivebayes {

class Classifier {

public:
    explicit Classifier(const Model& model);

    void ClassifyImageSet(ImageProcessor& imageProcessor);

    double ClassifyImage(Image& image);

    static double ValidateImageSetClassification(ImageProcessor& imageProcessor);

private:
    Model model_;
};

}

#endif //NAIVE_BAYES_CLASSIFIER_H
