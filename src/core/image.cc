#include <core/image.h>
#include <iostream>

namespace naivebayes {

Image::Image(int value) {
    this->value_ = value;
    classification_ = -1;
}

int Image::GetClassification() const {
    return classification_;
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

void Image::SetClassification(int classification) {
    this->classification_ = classification;
}

std::ostream& operator<<(std::ostream& os, Image& image) {
    os << image.value_ << std::endl;

    for (const std::vector<int>& vector : image.pixels_) {

        for (int i : vector) {
            os << i;
        }
        os << std::endl;
    }
    os <<std::endl;
    return os;
}

} // namespace naivebayes