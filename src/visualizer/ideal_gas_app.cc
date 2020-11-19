#include <core/model.h>
#include <visualizer/ideal_gas_app.h>

namespace idealgas {

namespace visualizer {

IdealGasApp::IdealGasApp()
    : particle_box_(glm::vec2(kMargin, kMargin),
                    kWindowLength - 3 * kMargin - histogramLength,
                    kWindowHeight - 2 * kMargin),
      histogram_box_(
          glm::vec2(kWindowLength - kMargin - histogramLength, kMargin),
          histogramLength, kWindowHeight - 2 * kMargin, kMargin / 2) {
  ci::app::setWindowSize((int)kWindowLength, (int)kWindowHeight);
}

void IdealGasApp::draw() {
  ci::Color8u background_color(0, 0, 0);  // black like my soul
  ci::gl::clear(background_color);

  particle_box_.Draw();
  particle_box_.Update();

  histogram_box_.InputData(particle_box_.GetModel().CreateVelHistogramData());
  histogram_box_.Draw();

  ci::gl::drawStringCentered(
      "Press Delete to clear the particle_box. Click mouse to add a particle. "
      "Toggle speed using Up/Down arrow keys.",
      glm::vec2(kWindowHeight / 2, kMargin / 2), ci::Color("white"),
      ci::Font("Arial", 20));

  ci::gl::drawStringCentered(
      "Press P to toggle particle type. Current selection: " +
          particle_box_.GetCurrentParticleType(),
      glm::vec2(kWindowHeight / 2, kWindowHeight - kMargin / 2),
      ci::Color("white"), ci::Font("Arial", 20));
}

void IdealGasApp::mouseDown(ci::app::MouseEvent event) {
  particle_box_.HandleBrush(event.getPos());
}

void IdealGasApp::mouseDrag(ci::app::MouseEvent event) {
  particle_box_.HandleBrush(event.getPos());
}

void IdealGasApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_UP:
      particle_box_.GetModel().IncreaseVelocity();
      break;

    case ci::app::KeyEvent::KEY_DOWN:
      particle_box_.GetModel().DecreaseVelocity();
      break;

    case ci::app::KeyEvent::KEY_p:
      particle_box_.IncrementParticleTypeIndex();
      break;

    case ci::app::KeyEvent::KEY_DELETE:
      particle_box_.Clear();
      break;
  }
}

}  // namespace visualizer

}  // namespace idealgas
