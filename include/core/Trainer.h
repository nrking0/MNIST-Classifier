#include <string>
#include <map>
#include <core/image.h>
#include <fstream>
#include <sstream>
#include <iostream>

namespace naivebayes {

class Trainer {
 public:
  Trainer();
  void display();
  void TrainProbClassC();

  friend std::istream& operator>>(std::istream& input, Trainer& data){
      std::string curr_line;
      while (std::getline(input, curr_line)) {
          if (std::isdigit(curr_line[0])) {
              Image image = Image(std::stoi(curr_line));
              data.images_.push_back(image);
          } else {
              std::vector<int> image_row;
              for (char pixel : curr_line) {
                  if (pixel == ' ') {
                      image_row.push_back(0);
                  } else {
                      image_row.push_back(1);
                  }
              }
              int size = data.images_.size() - 1;
              data.images_[size].AddPixelRow(image_row);
          }
      }
      return input;
  };



private:
    const static int kKValue = 1;
    const static int kNumShadingOptions = 2;
    const static int kNumValues = 10;
    std::vector<double> prob_class_c_values;
    std::map<int, Image> training_data_;
    std::vector<Image> images_;
};



}  // namespace naivebayes

