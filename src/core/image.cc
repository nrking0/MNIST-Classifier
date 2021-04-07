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

    int Image::GetPixelShade(int row, int col) const {
        return pixels_[row][col];
    }

    void Image::AddPixelRow(const std::vector<int>& row) {
        this->pixels_.push_back(row);
    }

} // namespace naivebayes