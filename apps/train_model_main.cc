#include <iostream>

#include <core/trainer.h>
#include <core/image_processor.h>
#include <core/image.h>
#include <fstream>


int main() {

    naivebayes::Trainer trainer = naivebayes::Trainer();
    naivebayes::ImageProcessor imageProcessor = naivebayes::ImageProcessor();
  std::ifstream input_file("../data/test_output.txt");
  if (input_file.is_open()) {
      input_file >> trainer;
      input_file.close();
  }
//  for (double d : trainer.GetProbClassC()) {
//      std::cout << d << std::endl;
//  }

  for (std::vector<std::vector<std::vector<double>>> a : trainer.GetProbPixelVals()) {
      for (std::vector<std::vector<double>> b : a) {
          for (std::vector<double> c : b) {
              for (double d : c) {
                  std::cout << d << std::endl;
              }
          }
      }
  }
//  imageProcessor.display();
//  trainer.TrainProbClassC(imageProcessor.GetImages());
//  trainer.TrainProbEachPixel(imageProcessor.GetImages());
//
//  std::ofstream output_file("../data/test_output.txt");
//  if (output_file.is_open()) {
//      output_file << trainer;
//      output_file.close();
//  }
  return 0;
}
