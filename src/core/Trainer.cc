#include <core/Trainer.h>

namespace naivebayes {

    Trainer::Trainer() {}

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

    void Trainer::display() {
        for (Image i : images_) {
            i.display();
        }
    }

}  // namespace naivebayes