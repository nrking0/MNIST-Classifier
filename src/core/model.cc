#include <core/model.h>

namespace naivebayes {

Model::Model() { }

void Model::Train(const ImageProcessor &imageProcessor) {
    const std::vector<Image>& images = imageProcessor.GetImages();
    this->TrainProbEachPixel(images);
    this->TrainProbClassC(images);
}

std::istream& operator>>(std::istream& input, Model& data) {
    std::string curr_line;
    bool reading_pixel_prob = false;
    while (std::getline(input, curr_line)) {
        // Checking for empty line at end of list and ignoring
        if (curr_line.empty() && reading_pixel_prob) {
            continue;

            // Checking for empty line that signifies move from class probabilities to pixel probabilities
        } else if (curr_line.empty() && !reading_pixel_prob) {
            reading_pixel_prob = true;
            std::getline(input, curr_line);
            // Setting image size from first line on pixel probabilities list
            data.image_size_ = std::stoi(curr_line);

            // Checking to see if pixel probability portion of file has been reached
        } else if (reading_pixel_prob) {

            // Reading pixel probability one line at a time sequentially through 4D Array
            for (size_t row = 0; row < data.image_size_; row++) {
                std::vector<std::vector<std::vector<double>>> columns;

                for (size_t col = 0; col < data.image_size_; col++) {
                    std::vector<std::vector<double>> values;

                    for (size_t val = 0; val < naivebayes::Model::kNumValues; val++) {
                        std::vector<double> shades;

                        for (size_t shade = 0; shade < naivebayes::Model::kNumShadingOptions; shade++) {
                            // Try/Catch loop to prevent any problems with reading doubles
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
            // If no prior conditions true, just reading probability class values at beginning of file
            data.prob_class_c_values.push_back(std::stod(curr_line));
        }
    }
    return input;
}

std::ostream& operator<<(std::ostream& os, Model& trainer) {
    for (double prob : trainer.prob_class_c_values) {
        // Outputting class probabilities line by line first
        os << prob << std::endl;
    }

    // Empty line to separate class probabilities from pixel probabilities
    os << std::endl;

    // First line of pixel probabilities is image size, so model knows size and can iterate properly
    os << trainer.image_size_ << std::endl;
    for (const std::vector<std::vector<std::vector<double>>> &rows : trainer.prob_pixel_shade_) {

        for (const std::vector<std::vector<double>> &columns : rows) {

            for (const std::vector<double> &values : columns) {

                for (const double prob : values) {
                    // Adding each probability of 4D array on new line
                    os << prob << std::endl;
                }
            }
        }
    }
    return os;
}

const std::vector<double> & Model::GetProbClassC() const {
    return prob_class_c_values;
}

const std::vector<std::vector<std::vector<std::vector<double>>>> & Model::GetProbPixelValues() const {
    return prob_pixel_shade_;
}

void Model::TrainProbClassC(const std::vector<Image>& images) {
    // Finding number of images belonging to each class then dividing by total image number
    for (size_t i = 0; i < kNumValues; i++) {
        double num_images = 0;
        for (const Image& image : images) {
            if (image.GetValue() == i) {
                num_images++;
            }
        }
        double prob = (num_images + kKValue) / (1.0 * images.size() + (kNumValues * kKValue));
        prob_class_c_values.push_back(prob);
    }
}

void Model::TrainProbEachPixel(const std::vector<Image>& images) {
    image_size_ = images[0].GetSize();

    // Iterating through all 4 dimensions of array then sequentially building each
    // subarray to push up to next dimension
   for (size_t row = 0; row < image_size_; row++) {
        std::vector<std::vector<std::vector<double>>> columns;

        for (size_t col = 0; col < image_size_; col++) {
            std::vector<std::vector<double>> values;

            for (size_t val = 0; val < kNumValues; val++) {
                std::vector<double> shades;

                for (size_t shade = 0; shade < kNumShadingOptions; shade++) {
                    // Calculating difference between pixels that match the given shade to total number of pixels
                    int num_images = 0;
                    int num_images_with_shade = 0;
                    for (const Image &image : images) {
                        if (image.GetValue() != val) continue;
                        if (image.GetPixelShade(row, col) == shade) {
                            num_images++;
                            num_images_with_shade++;
                        } else {
                            num_images++;
                        }
                    }
                    double prob =
                            (1.0 * kKValue + num_images_with_shade) / ((kNumShadingOptions * kKValue) + num_images);
                    shades.push_back(prob);
                }
                values.push_back(shades);
            }
            columns.push_back(values);
        }
        prob_pixel_shade_.push_back(columns);
    }
}

}  // namespace naivebayes