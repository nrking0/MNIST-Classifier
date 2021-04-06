#include <core/model.h>

namespace naivebayes {

    Model::Model() { }

    const std::vector<double> & Model::GetProbClassC() const {
        return prob_class_c_values;
    }

    const std::vector<std::vector<std::vector<std::vector<double>>>> & Model::GetProbPixelValues() const {
        return prob_pixel_shade_;
    }

    void Model::TrainProbClassC(const std::vector<Image>& images) {
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
       for (size_t row = 0; row < images[0].GetSize(); row++) {
            std::vector<std::vector<std::vector<double>>> columns;
            for (size_t col = 0; col < images[0].GetSize(); col++) {
                std::vector<std::vector<double>> values;
                for (size_t val = 0; val < kNumValues; val++) {
                    std::vector<double> shades;
                    for (size_t shade = 0; shade < kNumShadingOptions; shade++) {
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