#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "particle_box.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"

namespace halftoneparticle {

namespace visualizer {


class HalftoneParticleApp : public ci::app::App {
 public:
  HalftoneParticleApp();

  void draw() override;
  void mouseDown(ci::app::MouseEvent event) override;
  void mouseDrag(ci::app::MouseEvent event) override;
  void keyDown(ci::app::KeyEvent event) override;

  const double kWindowLength =
      875 + 100 + 291.6666;  // standard square + margin + histogram length
  const double kWindowHeight = 875;
  const double kMargin = 100;

 private:
  ParticleBox particle_box_;
    ci::gl::Texture2dRef  mTexture;
    ci::Surface mSurface;
    ci::Channel32f mChannel;


};

}  // namespace visualizer

}  // namespace halftoneparticle
