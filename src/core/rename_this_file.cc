#include <core/rename_this_file.h>

namespace naivebayes {

    Trainer::Trainer() {}


    void Trainer::display() {
        for (Image i : images_) {
            i.display();
        }
    }

}  // namespace naivebayes