#include <iostream>
#include <core/model.h>
#include <core/image_processor.h>
#include <core/image.h>


int main() {

//    naivebayes::Model model = naivebayes::Model();
//    naivebayes::ImageProcessor imageProcessor = naivebayes::ImageProcessor();
//
//  std::ifstream input_file("../data/trainingimagesandlabels.txt");
//  if (input_file.is_open()) {
//      input_file >> imageProcessor;
//      input_file.close();
//  }
//
//  imageProcessor.display();
//  model.TrainProbClassC(imageProcessor.GetImages());
//  model.TrainProbEachPixel(imageProcessor.GetImages());
//
//  std::ofstream output_file("../data/model_data.txt");
//  if (output_file.is_open()) {
//      output_file << model;
//      output_file.close();
//  }

    naivebayes::Model model = naivebayes::Model();
    naivebayes::ImageProcessor imageProcessor = naivebayes::ImageProcessor();

  std::ifstream input_file("../data/test.txt");
  if (input_file.is_open()) {
      input_file >> imageProcessor;
      input_file.close();
  }

  std::cout << imageProcessor;

//  model.TrainProbEachPixel(imageProcessor.GetImages());
//  for (std::vector<std::vector<std::vector<double>>> a : model.GetProbPixelValues()) {
//      for (std::vector<std::vector<double>> b : a) {
//          for (std::vector<double> c : b) {
//              for (double d : c) {
//                  std::cout << d << std::endl;
//              }
//          }
//      }
//  }

  return 0;
}
