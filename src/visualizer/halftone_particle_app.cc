#include <core/model.h>
#include <visualizer/halftone_particle_app.h>

namespace halftoneparticle {

    namespace visualizer {

        HalftoneParticleApp::HalftoneParticleApp() : particle_box_(glm::vec2(kMargin, kMargin),
                                                                   kWindowLength - 2 * kMargin,
                                                                   kWindowHeight - 2 * kMargin) {

            mChannel = ci::Channel32f(loadImage(loadAsset("testimage3.jpg")));
            const ci::Area img_area = mChannel.getBounds();
            ci::app::setWindowSize((int) img_area.x2, (int) img_area.y2);

            particle_box_ = ParticleBox(glm::vec2(kMargin, kMargin),
                                        img_area.x2 - 2 * kMargin,
                                        img_area.y2 - 2 * kMargin);
            particle_box_.LoadImage(mChannel);

//mSurface = ci::Surface(loadImage(loadAsset("testimage.jpg")));

//mChannel = ci::Channel(loadImage(loadAsset("testimage.jpg")));

            mTexture = ci::gl::Texture::create(mChannel);

        }

        void HalftoneParticleApp::draw() {
            ci::Color8u background_color(0, 0, 0);  // black like my soul
            ci::gl::clear(background_color);
            //ci::gl::draw(mTexture, getWindowBounds());
            //ci::gl::draw(mTexture);

            particle_box_.Draw();
            particle_box_.Update();

//  ci::gl::drawStringCentered(
//      "Press Delete to clear the particle_box. Click mouse to add a particle. "
//      "Toggle speed using Up/Down arrow keys.",
//      glm::vec2(kWindowHeight / 2, kMargin / 2), ci::Color("white"),
//      ci::Font("Arial", 20));
//
//  ci::gl::drawStringCentered(
//      "Press P to toggle particle type. Current selection: " +
//          particle_box_.GetCurrentParticleType(),
//      glm::vec2(kWindowHeight / 2, kWindowHeight - kMargin / 2),
//      ci::Color("white"), ci::Font("Arial", 20));
        }

        void HalftoneParticleApp::mouseDown(ci::app::MouseEvent event) {
            particle_box_.HandleBrush(event.getPos());
        }

        void HalftoneParticleApp::mouseDrag(ci::app::MouseEvent event) {
            particle_box_.HandleBrush(event.getPos());
        }

        void HalftoneParticleApp::keyDown(ci::app::KeyEvent event) {
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

}  // namespace halftoneparticle
