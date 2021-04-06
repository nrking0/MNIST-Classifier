#ifndef NAIVE_BAYES_IMAGE_PROCESSOR_H
#define NAIVE_BAYES_IMAGE_PROCESSOR_H

#include <iostream>
#include <core/image.h>

namespace naivebayes {

    class ImageProcessor {
    public:
        ImageProcessor();

        const std::vector<Image>& GetImages() const;

        void display() const;

        friend std::istream& operator>>(std::istream& is, ImageProcessor& imageProcessor) {
            std::string curr_line;
            while (std::getline(is, curr_line)) {
                if (std::isdigit(curr_line[0])) {
                    Image image = Image(std::stoi(curr_line));
                    imageProcessor.images_.push_back(image);
                } else {
                    std::vector<int> image_row;
                    for (char pixel : curr_line) {
                        if (pixel == ' ') {
                            image_row.push_back(0);
                        } else {
                            image_row.push_back(1);
                        }
                    }
                    int size = imageProcessor.images_.size() - 1;
                    imageProcessor.images_[size].AddPixelRow(image_row);
                }
            }
            return is;
        };

    private:
        std::vector<Image> images_;
    };


}

#endif //NAIVE_BAYES_IMAGE_PROCESSOR_H
