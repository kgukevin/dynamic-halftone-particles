
#include <visualizer/particle_box.h>

#include <utility>

namespace halftoneparticle {

    namespace visualizer {

        using glm::vec2;

        ParticleBox::ParticleBox(const vec2 &top_left_corner, double particle_box_width,
                                 double particle_box_height)
            : model_(top_left_corner, vec2(particle_box_width, particle_box_height)),
              top_left_corner_(top_left_corner),
              particle_box_height_(particle_box_height),
              particle_box_width_(particle_box_width) {

            model_.PreLoadHalftoneImage(top_left_corner, particle_box_width, particle_box_height, 20, 20, "white");

            //for (size_t x = 0; x < 160; x+=80) {
            //    Particle p1(top_left_corner + vec2(500, x), vec2(1, 0), 5, 1, "cyan");
            //    Particle p2(top_left_corner + vec2(700, x), vec2(-1, 0), 5, 1, "pink");
            //    model_.AddParticle(p1);
            //    model_.AddParticle(p2);
            //}
        }

        void ParticleBox::Draw() const {
            ci::gl::color(ci::Color("white"));
            vec2 bottom_right_corner = top_left_corner_ + vec2(particle_box_width_, particle_box_height_);
            ci::Rectf pixel_bounding_box(top_left_corner_, bottom_right_corner);
            ci::gl::drawStrokedRect(pixel_bounding_box);

            for (const Particle &particle : model_.get_particles()) {
                std::string color = particle.color();
                const char *svgkey = color.c_str();
                // convert char* svg key (color name) to rgb values
                ci::gl::color(ci::Color(ci::svgNameToRgb(svgkey)));

                //only drawn radius changes not actual radius
                ci::gl::drawSolidCircle(particle.position(), (img_channel_.getValue(particle.position())) * 7.0f);
            }
        }

        void ParticleBox::Update() {
            model_.UpdateMovement();
        }

        void ParticleBox::HandleParticleCreation(const vec2 &cursor_screen_coords) {
            if (IsWithinWalls(cursor_screen_coords)) {
                for (int num = 0; num < 10; num++) {
                    model_.CreateAndAddParticle(cursor_screen_coords, 1, 9, 1, particle_colors_[current_particle_index_]);
                }
            }
        }

        void ParticleBox::ChangeGravityOrigin(const vec2 &cursor_screen_coords) {
            model_.SetGravityOrigin(cursor_screen_coords);
        }

        bool ParticleBox::IsWithinWalls(const vec2 &brush_screen_coords) {
            vec2 bottom_right_corner = top_left_corner_ + vec2(particle_box_width_, particle_box_height_);
            if (top_left_corner_.x < brush_screen_coords.x && top_left_corner_.y < brush_screen_coords.y &&
                bottom_right_corner.x > brush_screen_coords.x && bottom_right_corner.y > brush_screen_coords.y) {
                return true;
            }
            return false;
        }

        Model &ParticleBox::GetModel() {
            return model_;
        }

        void ParticleBox::IncrementParticleTypeIndex() {
            current_particle_index_++;
            if (current_particle_index_ == particle_colors_.size()) {
                current_particle_index_ = 0;
            }
        }

        void ParticleBox::LoadImage(const ci::Channel32f &img_channel) {
            img_channel_ = img_channel;
        }

        void ParticleBox::Clear() {
            model_.Clear();
        }


    }// namespace visualizer

}// namespace halftoneparticle
