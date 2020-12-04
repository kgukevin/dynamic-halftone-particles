#include <visualizer/halftone_particle_app.h>

using halftoneparticle::visualizer::HalftoneParticleApp;

void prepareSettings(HalftoneParticleApp::Settings* settings) {
  settings->setResizable(true);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(HalftoneParticleApp, ci::app::RendererGl, prepareSettings);
