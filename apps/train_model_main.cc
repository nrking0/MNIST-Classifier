#include <iostream>
#include <core/model.h>
#include <core/image_processor.h>


int main() {

    naivebayes::Model model = naivebayes::Model();
    naivebayes::ImageProcessor imageProcessor = naivebayes::ImageProcessor();

  std::ifstream input_file("../data/trainingimagesandlabels.txt");
  if (input_file.is_open()) {
      input_file >> imageProcessor;
      input_file.close();
  }

  std::cout << imageProcessor;
  model.Train(imageProcessor);

  std::ofstream output_file("../data/model_data.txt");
  if (output_file.is_open()) {
      output_file << model;
      output_file.close();
  }

  return 0;
}
