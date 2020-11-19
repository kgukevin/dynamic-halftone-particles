#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "histogram_box.h"
#include "particle_box.h"

namespace idealgas {

namespace visualizer {

/**
 * Allows a user to simulate particle collisions and analyze particle
 * velocity histograms.
 */
class IdealGasApp : public ci::app::App {
 public:
  IdealGasApp();

  void draw() override;
  void mouseDown(ci::app::MouseEvent event) override;
  void mouseDrag(ci::app::MouseEvent event) override;
  void keyDown(ci::app::KeyEvent event) override;

  const double kWindowLength =
      875 + 100 + 291.6666;  // standard square + margin + histogram length
  const double kWindowHeight = 875;
  const double kMargin = 100;
  const double histogramLength = 291.6666;  // standard square / 3

 private:
  ParticleBox particle_box_;
  HistogramBox histogram_box_;
};

}  // namespace visualizer

}  // namespace idealgas
