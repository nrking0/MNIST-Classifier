#include <catch2/catch.hpp>
#include <core/image_processor.h>
#include <core/image.h>
#include <fstream>


using naivebayes::ImageProcessor;
using naivebayes::Image;

TEST_CASE("Read in image") {

    SECTION("Check Images") {
        ImageProcessor imageProcessor = ImageProcessor();

        std::ifstream input_file("/Users/nrking0/code/cinder_0.9.2_mac/my-projects/naive-bayes/data/test.txt");
        if (input_file.is_open()) {
            input_file >> imageProcessor;
            input_file.close();
        }

        std::cout << imageProcessor.GetImages().size();
        const std::vector<Image>& images = imageProcessor.GetImages();
        REQUIRE(imageProcessor.GetImages().size() == 2);
        REQUIRE(images[0].GetValue() == 1);
        REQUIRE(images[0].GetPixelShade(0,0) == 1);
        REQUIRE(images[0].GetPixelShade(0,1) == 1);
        REQUIRE(images[0].GetPixelShade(1,0) == 0);
        REQUIRE(images[0].GetPixelShade(1,1) == 1);

        REQUIRE(images[1].GetValue() == 0);
        REQUIRE(images[1].GetPixelShade(0,0) == 0);
        REQUIRE(images[1].GetPixelShade(0,1) == 1);
        REQUIRE(images[1].GetPixelShade(1,0) == 0);
        REQUIRE(images[1].GetPixelShade(1,1) == 1);
    }

    SECTION("Read in from bad file path") {
        ImageProcessor imageProcessor = ImageProcessor();

        std::ifstream input_file("notexistingfile.txt");
        if (input_file.is_open()) {
            input_file >> imageProcessor;
            input_file.close();
        }

        REQUIRE(imageProcessor.GetImages().empty());
    }
}
