#include <iostream>

#include <core/rename_this_file.h>
#include <core/image.h>
#include <fstream>

// TODO: You may want to change main's signature to take in argc and argv
int main() {

    naivebayes::Trainer trainer = naivebayes::Trainer();
  std::ifstream input_file("../data/trainingimagesandlabels.txt");
  if (input_file.is_open()) {
      input_file >> trainer;
      input_file.close();
  }
  trainer.display();
  return 0;
}
