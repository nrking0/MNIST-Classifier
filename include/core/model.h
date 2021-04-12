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
    friend std::istream &operator>>(std::istream &input, Model &data);

    /**
     * Overloading the output operator to put the values for this model into an
     * external file to avoid unneeded repeated calculations.
     *
     * @param os output stream
     * @param trainer the object that is being outputted
     * @return the output stream after finished
     */
    friend std::ostream &operator<<(std::ostream &os, Model &trainer);


private:
    const static int kKValue = 1;
    const static int kNumShadingOptions = 2;
    const static int kNumValues = 10;
    std::vector<std::vector<std::vector<std::vector<double>>>> prob_pixel_shade_;
    std::vector<double> prob_class_c_values;
    int image_size_;
};


}  // namespace naivebayes

