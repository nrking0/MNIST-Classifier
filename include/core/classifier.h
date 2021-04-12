#ifndef NAIVE_BAYES_CLASSIFIER_H
#define NAIVE_BAYES_CLASSIFIER_H

#include <core/image.h>
#include <core/image_processor.h>
#include <core/model.h>

namespace naivebayes {

class Classifier {

public:
    Classifier();

    static void ClassifyImageSet(ImageProcessor& imageProcessor, Model& model);

    static double ValidateImageSetClassification(ImageProcessor& imageProcessor);
};

}

#endif //NAIVE_BAYES_CLASSIFIER_H
