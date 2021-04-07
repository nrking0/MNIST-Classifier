#include <catch2/catch.hpp>
#include <core/model.h>
#include <core/image_processor.h>

using naivebayes::ImageProcessor;
using naivebayes::Model;

TEST_CASE("Training Model") {
    ImageProcessor imageProcessor = ImageProcessor();
    Model model = Model();

    std::ifstream input_file("/Users/nrking0/code/cinder_0.9.2_mac/my-projects/naive-bayes/data/test.txt");
    if (input_file.is_open()) {
        input_file >> imageProcessor;
        input_file.close();
    }

    model.TrainProbClassC(imageProcessor.GetImages());
    model.TrainProbEachPixel(imageProcessor.GetImages());

    SECTION("Check Class Probabilities") {
        const std::vector<double> &prob_classes = model.GetProbClassC();
        REQUIRE(prob_classes[0] == Approx(0.166).epsilon(0.01));
        REQUIRE(prob_classes[1] == Approx(0.166).epsilon(0.01));
    }

    SECTION("Check individual pixel probabilities") {
        const std::vector<std::vector<std::vector<std::vector<double>>>> &prob_pixels = model.GetProbPixelValues();
        // Pixel at (0,0)
        REQUIRE(prob_pixels[0][0][0][0] == Approx(0.666).epsilon(0.01));
        REQUIRE(prob_pixels[0][0][0][1] == Approx(0.333).epsilon(0.01));
        REQUIRE(prob_pixels[0][0][1][0] == Approx(0.333).epsilon(0.01));
        REQUIRE(prob_pixels[0][0][1][1] == Approx(0.666).epsilon(0.01));

        // Pixel at (0,1)
        REQUIRE(prob_pixels[0][1][0][0] == Approx(0.333).epsilon(0.01));
        REQUIRE(prob_pixels[0][1][0][1] == Approx(0.666).epsilon(0.01));
        REQUIRE(prob_pixels[0][1][1][0] == Approx(0.333).epsilon(0.01));
        REQUIRE(prob_pixels[0][1][1][1] == Approx(0.666).epsilon(0.01));

        // Pixel at (1,0)
        REQUIRE(prob_pixels[1][0][0][0] == Approx(0.666).epsilon(0.01));
        REQUIRE(prob_pixels[1][0][0][1] == Approx(0.333).epsilon(0.01));
        REQUIRE(prob_pixels[1][0][1][0] == Approx(0.666).epsilon(0.01));
        REQUIRE(prob_pixels[1][0][1][1] == Approx(0.333).epsilon(0.01));

        // Pixel at (1,1)
        REQUIRE(prob_pixels[1][1][0][0] == Approx(0.333).epsilon(0.01));
        REQUIRE(prob_pixels[1][1][0][1] == Approx(0.666).epsilon(0.01));
        REQUIRE(prob_pixels[1][1][1][0] == Approx(0.333).epsilon(0.01));
        REQUIRE(prob_pixels[1][1][1][1] == Approx(0.666).epsilon(0.01));
    }
}

TEST_CASE("Test writing model to file") {
    ImageProcessor imageProcessor = ImageProcessor();
    Model model = Model();

    std::ifstream input_file("/Users/nrking0/code/cinder_0.9.2_mac/my-projects/naive-bayes/data/test.txt");
    if (input_file.is_open()) {
        input_file >> imageProcessor;
        input_file.close();
    }

    model.TrainProbClassC(imageProcessor.GetImages());
    model.TrainProbEachPixel(imageProcessor.GetImages());

    std::ofstream output_file("/Users/nrking0/code/cinder_0.9.2_mac/my-projects/naive-bayes/data/test_output.txt");
    if (output_file.is_open()) {
        output_file << model;
        output_file.close();
    }

    std::ifstream input_file2("/Users/nrking0/code/cinder_0.9.2_mac/my-projects/naive-bayes/data/test_output.txt");
    // Below assisted by: https://stackoverflow.com/questions/2390912/checking-for-an-empty-file-in-c
    REQUIRE(input_file2.peek() != std::ifstream::traits_type::eof());
}


TEST_CASE("Reading model data in from file") {
    Model model = Model();

    std::ifstream output_file("/Users/nrking0/code/cinder_0.9.2_mac/my-projects/naive-bayes/data/test_output.txt");
    if (output_file.is_open()) {
        output_file >> model;
        output_file.close();
    }

    SECTION("Check Class Probabilities") {
        const std::vector<double> &prob_classes = model.GetProbClassC();
        REQUIRE(prob_classes[0] == Approx(0.166).epsilon(0.01));
        REQUIRE(prob_classes[1] == Approx(0.166).epsilon(0.01));
    }

    SECTION("Check individual pixel probabilities") {
        const std::vector<std::vector<std::vector<std::vector<double>>>> &prob_pixels = model.GetProbPixelValues();
        // Pixel at (0,0)
        REQUIRE(prob_pixels[0][0][0][0] == Approx(0.666).epsilon(0.01));
        REQUIRE(prob_pixels[0][0][0][1] == Approx(0.333).epsilon(0.01));
        REQUIRE(prob_pixels[0][0][1][0] == Approx(0.333).epsilon(0.01));
        REQUIRE(prob_pixels[0][0][1][1] == Approx(0.666).epsilon(0.01));

        // Pixel at (0,1)
        REQUIRE(prob_pixels[0][1][0][0] == Approx(0.333).epsilon(0.01));
        REQUIRE(prob_pixels[0][1][0][1] == Approx(0.666).epsilon(0.01));
        REQUIRE(prob_pixels[0][1][1][0] == Approx(0.333).epsilon(0.01));
        REQUIRE(prob_pixels[0][1][1][1] == Approx(0.666).epsilon(0.01));

        // Pixel at (1,0)
        REQUIRE(prob_pixels[1][0][0][0] == Approx(0.666).epsilon(0.01));
        REQUIRE(prob_pixels[1][0][0][1] == Approx(0.333).epsilon(0.01));
        REQUIRE(prob_pixels[1][0][1][0] == Approx(0.666).epsilon(0.01));
        REQUIRE(prob_pixels[1][0][1][1] == Approx(0.333).epsilon(0.01));

        // Pixel at (1,1)
        REQUIRE(prob_pixels[1][1][0][0] == Approx(0.333).epsilon(0.01));
        REQUIRE(prob_pixels[1][1][0][1] == Approx(0.666).epsilon(0.01));
        REQUIRE(prob_pixels[1][1][1][0] == Approx(0.333).epsilon(0.01));
        REQUIRE(prob_pixels[1][1][1][1] == Approx(0.666).epsilon(0.01));
    }
}

TEST_CASE("Read in from bad file path") {
    Model model = Model();

    std::ifstream output_file("randombadfile.txt");
    if (output_file.is_open()) {
        output_file >> model;
        output_file.close();
    }

    REQUIRE(model.GetProbPixelValues().empty());
    REQUIRE(model.GetProbClassC().empty());
}