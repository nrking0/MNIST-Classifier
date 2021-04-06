#include <string>
#include <map>
#include <core/image.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

namespace naivebayes {

class Trainer {
 public:
  Trainer();
  void TrainProbClassC(const std::vector<Image>& images);
  void TrainProbEachPixel(const std::vector<Image>& images);
  const std::vector<double>& GetProbClassC() const;
  const std::vector<std::vector<std::vector<std::vector<double>>>>& GetProbPixelVals() const;

  friend std::istream& operator>>(std::istream& input, Trainer& data){
      std::string curr_line;
      bool pixel_probs = false;
      while (std::getline(input, curr_line)) {
          if (curr_line.empty() && pixel_probs) {
              continue;
          } else if (curr_line.empty() && !pixel_probs) {
              pixel_probs = true;
              std::getline(input, curr_line);
              data.image_size_ = std::stoi(curr_line);
          } else if (pixel_probs) {

              for (int row = 0; row < data.image_size_; row++) {
                  std::vector<std::vector<std::vector<double>>> columns;
                  for (int col = 0; col < data.image_size_; col++) {
                      std::vector<std::vector<double>> values;
                      for (int val = 0; val < kNumValues; val++) {
                          std::vector<double> shades;
                          for (int shade = 0; shade < kNumShadingOptions; shade++) {
                              try {

                              shades.push_back(std::stod(curr_line));
                              } catch (std::exception& e) {
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

  friend std::ostream& operator<<(std::ostream& os, Trainer& trainer) {
      for (double prob : trainer.prob_class_c_values) {
          os << prob << std::endl;
      }
      os << std::endl;
      os << trainer.image_size_ << std::endl;
      for (const std::vector<std::vector<std::vector<double>>>& rows : trainer.prob_pixel_shade_) {
          for (const std::vector<std::vector<double>>& columns : rows) {
              for (const std::vector<double>& values : columns) {
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
    std::vector<Image> images_;
    int image_size_;
};



}  // namespace naivebayes

