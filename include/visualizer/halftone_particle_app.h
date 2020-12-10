#pragma once

#include "cinder/ImageIo.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/gl.h"
#include "particle_box.h"

namespace halftoneparticle {

    namespace visualizer {


        class HalftoneParticleApp : public ci::app::App {
        public:
            HalftoneParticleApp();

            /**
             * Allows for drag and drop image.
             * @param event
             */
            void fileDrop(ci::app::FileDropEvent event);

            void draw() override;
            void mouseDown(ci::app::MouseEvent event) override;
            void mouseDrag(ci::app::MouseEvent event) override;
            void keyDown(ci::app::KeyEvent event) override;

            const double kWindowLength = 875 + 100;// standard square + margin
            const double kWindowHeight = 875;
            const double kMargin = 100;

        private:
            ParticleBox particle_box_;
            ci::gl::Texture2dRef mTexture;
            ci::Surface mSurface;
            ci::Channel32f mChannel;
        };

    }// namespace visualizer

}// namespace halftoneparticle
