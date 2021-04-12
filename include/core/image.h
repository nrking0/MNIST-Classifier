#ifndef NAIVE_BAYES_IMAGE_H
#define NAIVE_BAYES_IMAGE_H

#include <vector>
#include <iostream>

namespace naivebayes {

    /** Class representing an Image. */
class Image {
public:
    /**
     * Basic constructor to set up image.
     *
     * @param value this is the number that is being shown on the image
     */
    explicit Image(int value);

    /**
     * Adds a row of pixels to the image array. Used when inputting image.
     *
     * @param row vector of ints representing a row of pixels
     */
    void AddPixelRow(const std::vector<int>& row);

    /**
     * Simple overload of output operator in order to print out image.
     *
     * @param os output stream
     * @param image image that will be displayed
     * @return the output stream after finished
     */
    friend std::ostream& operator<<(std::ostream& os, Image& image);

    int GetValue() const;
    int GetSize() const;
    int GetPixelShade(int row, int col) const;

private:
    int value_;
    std::vector<std::vector<int>> pixels_;
};

} // namespace naivebayes

#endif //NAIVE_BAYES_IMAGE_H
