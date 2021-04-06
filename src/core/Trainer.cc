#include <core/Trainer.h>

namespace naivebayes {

    Trainer::Trainer() { }

    void Trainer::TrainProbClassC() {
        for (size_t i = 0; i < kNumValues; i++) {
            double num_images = 0;
            for (Image image : images_) {
                if (image.GetValue() == i) {
                    num_images++;
                }
            }
            double prob = (num_images + kKValue) / (1.0 * images_.size() + (kNumValues * kKValue));
            prob_class_c_values.push_back(prob);
        }
    }

    void Trainer::TrainProbEachPixel() {
        //std::cout << "hi";
//        prob_pixel_shade_ = std::vector<std::vector<std::vector<std::vector<double>>>>(images_[0].GetSize(),
//                                                                                      std::vector<std::vector<std::vector<double>>>(
//                                                                                              images_[0].GetSize(),
//                                                                                              std::vector<std::vector<double>>(
//                                                                                                      kNumValues,
//                                                                                                      std::vector<double>(
//                                                                                                              kNumShadingOptions,
//                                                                                                              0))));

        for (int row = 0; row < images_[0].GetSize(); row++) {
            std::vector<std::vector<std::vector<double>>> columns;
            for (int col = 0; col < images_[0].GetSize(); col++) {
                std::vector<std::vector<double>> values;
                for (int val = 0; val < kNumValues; val++) {
                    std::vector<double> shades;
                    for (int shade = 0; shade < kNumShadingOptions; shade++) {
                        int num_images = 0;
                        int num_images_with_shade = 0;
                        for (const Image &image : images_) {
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

    void Trainer::display() {
        for (Image i : images_) {
            i.display();
        }
    }

}  // namespace naivebayes