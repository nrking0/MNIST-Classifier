#include <core/image.h>
#include <iostream>

namespace naivebayes {

    Image::Image(int value) {
        this->value_ = value;
    }

    int Image::GetValue() const {
        return this->value_;
    }

    int Image::GetSize() const {
        if (!pixels_.empty()) {
            return pixels_[0].size();
        } else {
            return 0;
        }
    }

    int Image::GetPixelShade(const int row, const int col) const {
        return pixels_[row][col];
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