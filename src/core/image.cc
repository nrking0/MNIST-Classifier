#include <core/image.h>
#include <iostream>

namespace naivebayes {

    Image::Image(int value) {
        this->value_ = value;
    }

    int Image::GetValue() const {
        return this->value_;
    }

    void Image::AddPixelRow(const std::vector<int> row) {
        this->pixels_.push_back(row);
    }

    void Image::display() {
        for (std::vector<int> v : pixels_) {
            for (int i : v) {
                std::cout << i;
            }
            std::cout << std::endl;
        }
        std::cout <<std::endl;
    }
}