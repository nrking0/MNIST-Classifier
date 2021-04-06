#include <iostream>

#include <core/Trainer.h>
#include <core/image.h>
#include <fstream>


int main() {

    naivebayes::Trainer trainer = naivebayes::Trainer();
  std::ifstream input_file("../data/test.txt");
  if (input_file.is_open()) {
      input_file >> trainer;
      input_file.close();
  }
  trainer.display();

  trainer.TrainProbEachPixel();

  return 0;
}
