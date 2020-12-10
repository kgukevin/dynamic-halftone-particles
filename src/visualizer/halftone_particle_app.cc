#include <core/model.h>
#include <visualizer/halftone_particle_app.h>

namespace halftoneparticle {

    namespace visualizer {

        HalftoneParticleApp::HalftoneParticleApp() : particle_box_(glm::vec2(kMargin, kMargin),
                                                                   kWindowLength - 2 * kMargin,
                                                                   kWindowHeight - 2 * kMargin) {

            mChannel = ci::Channel32f(loadImage(loadAsset("testimage2.jpg"))); //default image
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

        void HalftoneParticleApp::fileDrop(ci::app::FileDropEvent event) {
            const ci::fs::path& path = event.getFile(0);
            mChannel = ci::Channel32f(cinder::loadImage(path));
            const ci::Area img_area = mChannel.getBounds();
            ci::app::setWindowSize((int) img_area.x2, (int) img_area.y2);

            particle_box_ = ParticleBox(glm::vec2(kMargin, kMargin),
                                        img_area.x2 - 2 * kMargin,
                                        img_area.y2 - 2 * kMargin);
            particle_box_.LoadImage(mChannel);
        }

        void HalftoneParticleApp::draw() {
            ci::Color8u background_color(0, 0, 0);// black like my soul
            ci::gl::clear(background_color);
            //ci::gl::draw(mTexture, getWindowBounds());
            //ci::gl::draw(mTexture);

            particle_box_.Draw();
            particle_box_.Update();
        }

        void HalftoneParticleApp::mouseDown(ci::app::MouseEvent event) {
            particle_box_.HandleParticleCreation(event.getPos());
            if (event.isShiftDown()) {
                particle_box_.ChangeGravityOrigin(event.getPos());
            }
        }

        void HalftoneParticleApp::mouseDrag(ci::app::MouseEvent event) {
            particle_box_.HandleParticleCreation(event.getPos());
            if (event.isShiftDown()) {
                particle_box_.ChangeGravityOrigin(event.getPos());
            }
        }

        void HalftoneParticleApp::keyDown(ci::app::KeyEvent event) {
            switch (event.getCode()) {
                case ci::app::KeyEvent::KEY_UP:
                    particle_box_.GetModel().IncreaseVelocity();
                    break;

                case ci::app::KeyEvent::KEY_DOWN:
                    particle_box_.GetModel().DecreaseVelocity();
                    break;

                case ci::app::KeyEvent::KEY_g:
                    particle_box_.IncrementParticleTypeIndex();
                    break;

                case ci::app::KeyEvent::KEY_o: {
                    ci::fs::path path = getOpenFilePath("", ci::ImageIo::getLoadExtensions());
                    mChannel = ci::Channel32f(cinder::loadImage(path));
                    const ci::Area img_area = mChannel.getBounds();
                    ci::app::setWindowSize((int) img_area.x2, (int) img_area.y2);

                    particle_box_ = ParticleBox(glm::vec2(kMargin, kMargin),
                                                img_area.x2 - 2 * kMargin,
                                                img_area.y2 - 2 * kMargin);
                    particle_box_.LoadImage(mChannel);
                    break;
                }

                case ci::app::KeyEvent::KEY_DELETE:
                    particle_box_.Clear();
                    break;
            }
        }

    }// namespace visualizer

}// namespace halftoneparticle
