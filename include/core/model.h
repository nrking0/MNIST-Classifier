#include <string>
#include <map>
#include <core/image.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

namespace naivebayes {

    /** Classes representing a naive-bayes model. */
    class Model {
    public:
        /** Basic starter constructor. */
        Model();

        /**
         * Trains the model based on images that are received from image processor. This specific method
         * trains the values associated with the overall probability that an image belongs to a certain class.
         *
         * @param images vector of images that is made by image processor from an external file
         */
        void TrainProbClassC(const std::vector<Image> &images);

        /**
         * Trains the probability that a pixel belonging to each individual class will be each
         * shade. This will result in a 4D array with all probabilities.
         *
         * @param images images vector of images that is made by image processor from an external file
         */
        void TrainProbEachPixel(const std::vector<Image> &images);


        const std::vector<double> &GetProbClassC() const;
        const std::vector<std::vector<std::vector<std::vector<double>>>> &GetProbPixelValues() const;

        /**
         * Overload for input operator, takes in file data from a previous model and matches data to class structures.
         *
         * @param input input stream, in this case a file
         * @param data the object that the data is being put into
         * @return input stream after finished
         */
        friend std::istream &operator>>(std::istream &input, Model &data) {
            std::string curr_line;
            bool reading_pixel_prob = false;
            while (std::getline(input, curr_line)) {
                if (curr_line.empty() && reading_pixel_prob) {
                    continue;
                } else if (curr_line.empty() && !reading_pixel_prob) {
                    reading_pixel_prob = true;
                    std::getline(input, curr_line);
                    data.image_size_ = std::stoi(curr_line);
                } else if (reading_pixel_prob) {
                    for (size_t row = 0; row < data.image_size_; row++) {
                        std::vector<std::vector<std::vector<double>>> columns;
                        for (size_t col = 0; col < data.image_size_; col++) {
                            std::vector<std::vector<double>> values;
                            for (size_t val = 0; val < kNumValues; val++) {
                                std::vector<double> shades;
                                for (size_t shade = 0; shade < kNumShadingOptions; shade++) {
                                    try {

                                        shades.push_back(std::stod(curr_line));
                                    } catch (std::exception &e) {
                                        std::getline(input, curr_line);
                                        continue;
                                    }
                                    std::getline(input, curr_line);
                                }
                                values.push_back(shades);
                            }
                            columns.push_back(values);
                        }
                        data.prob_pixel_shade_.push_back(columns);
                    }
                } else {
                    data.prob_class_c_values.push_back(std::stod(curr_line));
                }
            }
            return input;
        };

        /**
         * Overloading the output operator to put the values for this model into an
         * external file to avoid unneeded repeated calculations.
         *
         * @param os output stream
         * @param trainer the object that is being outputted
         * @return the output stream after finished
         */
        friend std::ostream &operator<<(std::ostream &os, Model &trainer) {
            for (double prob : trainer.prob_class_c_values) {
                os << prob << std::endl;
            }
            os << std::endl;
            os << trainer.image_size_ << std::endl;
            for (const std::vector<std::vector<std::vector<double>>> &rows : trainer.prob_pixel_shade_) {
                for (const std::vector<std::vector<double>> &columns : rows) {
                    for (const std::vector<double> &values : columns) {
                        for (const double prob : values) {
                            os << prob << std::endl;
                        }
                    }
                }
            }
            return os;
        };


    private:
        const static int kKValue = 1;
        const static int kNumShadingOptions = 2;
        const static int kNumValues = 10;
        std::vector<std::vector<std::vector<std::vector<double>>>> prob_pixel_shade_;
        std::vector<double> prob_class_c_values;
        int image_size_;
    };


}  // namespace naivebayes

