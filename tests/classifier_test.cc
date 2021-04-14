#include <catch2/catch.hpp>
#include <core/classifier.h>
#include <core/model.h>
#include <core/image_processor.h>
#include <core/image.h>


TEST_CASE("Classifier") {
    Model model = Model();
    ImageProcessor imageProcessor = ImageProcessor();

    std::ifstream input_file("/Users/nrking0/code/cinder_0.9.2_mac/my-projects/naive-bayes/data/test_output.txt");
    if (input_file.is_open()) {
        input_file >> model;
        input_file.close();
    }

    std::ifstream input_file2("/Users/nrking0/code/cinder_0.9.2_mac/my-projects/naive-bayes/data/test_data.txt");
    if (input_file2.is_open()) {
        input_file2 >> imageProcessor;
        input_file2.close();
    }

    Calssifier classifier = Classifier(model);

    std::vector<double> likelihoods = classifier.ClassifyImage(imageProcessor.GetImages()[0]);

    SECTION("Check likelihoods") {
        REQUIRE(likelihoods[0] == Approx(-4.106).epsilon(0.01));
        REQUIRE(likelihoods[1] == Approx(-4.799).epsilon(0.01));
    }

    SECTION("Check Classifier") {
        REQUIRE(imageProcessor.GetImages()[0].GetClassification() == 0);
    }

    SECTION("Check Validation") {
        REQUIRE(Classifier::ValidateImageSetClassification(imageProcessor) == 1)
    }
}

TEST_CASE("Check Accuracy for real set") {
    Model model = Model();
    ImageProcessor imageProcessor = ImageProcessor();

    std::ifstream input_file("/Users/nrking0/code/cinder_0.9.2_mac/my-projects/naive-bayes/data/test_data.txt");
    if (input_file.is_open()) {
    input_file >> imageProcessor;
    input_file.close();
    }

    std::ifstream input_file2("/Users/nrking0/code/cinder_0.9.2_mac/my-projects/naive-bayes/data/test_output.txt");
    if (input_file2.is_open()) {
    input_file2 >> model;
    input_file2.close();
    }

    Classifier classifier = Classifier(model);
    classifier.ClassifyImageSet(imageProcessor);
    double accuracy = Classifier::ValidateImageSetClassification(imageProcessor);

    REQUIRE(accuracy > 0.7);
}
