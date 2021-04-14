#include <iostream>

#include <core/image_processor.h>
#include <core/classifier.h>


int main() {

    naivebayes::Model model = naivebayes::Model();
    naivebayes::ImageProcessor imageProcessor = naivebayes::ImageProcessor();

//  std::ifstream input_file("../data/test.txt");
//  if (input_file.is_open()) {
//      input_file >> imageProcessor;
//      input_file.close();
//  }
//
//  std::cout << imageProcessor;
//  model.Train(imageProcessor);
//
//  std::ofstream output_file("../data/test_output.txt");
//  if (output_file.is_open()) {
//      output_file << model;
//      output_file.close();
//  }



    std::ifstream input_file("../data/test_data.txt");
    if (input_file.is_open()) {
        input_file >> imageProcessor;
        input_file.close();
    }

    std::ifstream input_file2("../data/test_output.txt");
    if (input_file2.is_open()) {
        input_file2 >> model;
        input_file2.close();
    }

    naivebayes::Classifier classifier = naivebayes::Classifier(model);
    classifier.ClassifyImageSet(imageProcessor);

    for (const naivebayes::Image& image : imageProcessor.GetImages()) {
        std::cout << image.GetValue() << std::endl;
        std::cout << image.GetClassification() << std::endl;
        std::cout << std::endl;
    }

    double accuracy = naivebayes::Classifier::ValidateImageSetClassification(imageProcessor);
    std::cout << accuracy << std::endl;

    std::vector<double> prob1 = classifier.ClassifyImage(imageProcessor.GetImages()[0]);
    for (double d : prob1) {
        std::cout << d << std::endl;
    }


  return 0;
}
