#include <catch2/catch.hpp>
#include <core/image.h>

using naivebayes::Image;

TEST_CASE("Basic Getters") {
    Image image = Image(5);

    SECTION("Get Value") {
        REQUIRE(image.GetValue() == 5);
    }

    SECTION("Get Size when empty") {
        REQUIRE(image.GetSize() == 0);
    }
}

TEST_CASE("Test basic image") {
    Image image = Image(5);
    image.AddPixelRow(std::vector<int>({0,1}));
    image.AddPixelRow(std::vector<int>({0,0}));

    SECTION("Get size") {
        REQUIRE(image.GetSize() == 2);
    }

    SECTION("Get Pixel value") {
        REQUIRE(image.GetPixelShade(0,0) == 0);
        REQUIRE(image.GetPixelShade(0,1) == 1);
        REQUIRE(image.GetPixelShade(1,0) == 0);
        REQUIRE(image.GetPixelShade(1,1) == 0);
    }
}

