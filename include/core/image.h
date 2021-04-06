#ifndef NAIVE_BAYES_IMAGE_H
#define NAIVE_BAYES_IMAGE_H

#include <vector>

namespace naivebayes {

    class Image {
    public:
        Image(int value);
        void AddPixelRow(const std::vector<int> row);
        void display();

    private:
        int value_;
        std::vector<std::vector<int>> pixels_;
    };
}

#endif //NAIVE_BAYES_IMAGE_H
