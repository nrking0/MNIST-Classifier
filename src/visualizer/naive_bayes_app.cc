#include <visualizer/naive_bayes_app.h>

namespace naivebayes {

namespace visualizer {

NaiveBayesApp::NaiveBayesApp()
    : sketchpad_(glm::vec2(kMargin, kMargin), kImageDimension,
                 kWindowSize - 2 * kMargin) {
  ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);

    naivebayes::Model model;
    std::ifstream input_file("/Users/nrking0/code/cinder_0.9.2_mac/my-projects/naive-bayes/data/model_data.txt");
    if (input_file.is_open()) {
        input_file >> model;
        input_file.close();
    }

    classifier_ = naivebayes::Classifier(model);
}

void NaiveBayesApp::draw() {
  ci::Color8u background_color(255, 246, 148);  // light yellow
  ci::gl::clear(background_color);

  sketchpad_.Draw();

  ci::gl::drawStringCentered(
      "Press Delete to clear the sketchpad. Press Enter to make a prediction.",
      glm::vec2(kWindowSize / 2, kMargin / 2), ci::Color("black"));

  ci::gl::drawStringCentered(
      "Prediction: " + std::to_string(current_prediction_),
      glm::vec2(kWindowSize / 2, kWindowSize - kMargin / 2), ci::Color("blue"));
}

void NaiveBayesApp::mouseDown(ci::app::MouseEvent event) {
  sketchpad_.HandleBrush(event.getPos());
}

void NaiveBayesApp::mouseDrag(ci::app::MouseEvent event) {
  sketchpad_.HandleBrush(event.getPos());
}

void NaiveBayesApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_BACKSPACE:
        sketchpad_.Clear();
        current_prediction_ = -1;
        break;
    case ci::app::KeyEvent::KEY_RETURN:
        Image image = Image(sketchpad_.GetPixelShadeVector());
        classifier_.ClassifyImage(image);
        current_prediction_ = image.GetClassification();
        break;

  }
}

}  // namespace visualizer

}  // namespace naivebayes
