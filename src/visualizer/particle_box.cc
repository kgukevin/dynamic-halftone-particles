
#include <visualizer/particle_box.h>

namespace idealgas {

    namespace visualizer {

        using glm::vec2;

        ParticleBox::ParticleBox(const vec2 &top_left_corner, double particle_box_width,
                             double particle_box_height)
                : model_(top_left_corner, vec2(particle_box_width, particle_box_height)), top_left_corner_(top_left_corner),
                  particle_box_height_(particle_box_height),
                  particle_box_width_(particle_box_width) {

        }

        void ParticleBox::Draw() const {
            ci::gl::color(ci::Color("white"));
            vec2 bottom_right_corner = top_left_corner_ + vec2(particle_box_width_, particle_box_height_);
            ci::Rectf pixel_bounding_box(top_left_corner_, bottom_right_corner);
            ci::gl::drawStrokedRect(pixel_bounding_box);

            for (const Particle &particle : model_.get_particles()) {
                std::string color = particle.color();
                const char* svgkey = color.c_str();
                // convert char* svg key (color name) to rgb values
                ci::gl::color(ci::Color(ci::svgNameToRgb(svgkey)));

                ci::gl::drawSolidCircle(particle.position(), particle.radius());
            }
        }

        void ParticleBox::Update() {
            model_.UpdateMove();
        }

        void ParticleBox::HandleBrush(const vec2 &brush_screen_coords) {
            if (IsWithinWalls(brush_screen_coords)) {

                if (particle_types_[current_particle_index_] == "darkorange") {
                    model_.CreateAndAddParticle(brush_screen_coords, 4, 7, 5, "darkorange");
                }
                if (particle_types_[current_particle_index_] == "cyan") {
                    model_.CreateAndAddParticle(brush_screen_coords, 6, 4, 3, "cyan");
                }
                if (particle_types_[current_particle_index_] == "deeppink") {
                    model_.CreateAndAddParticle(brush_screen_coords, 2, 10, 7, "deeppink");
                }
                if (particle_types_[current_particle_index_] == "mediumspringgreen") {
                    model_.CreateAndAddParticle(brush_screen_coords, 2, 5, 4.5, "mediumspringgreen");
                }

            }
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

        const std::string ParticleBox::GetCurrentParticleType() {
            return particle_types_[current_particle_index_];
        }

        void ParticleBox::IncrementParticleTypeIndex() {
            current_particle_index_++;
            if (current_particle_index_ == particle_types_.size()) {
                current_particle_index_ = 0;
            }
        }

        void ParticleBox::Clear() {
            // TODO: implement this method
            model_.Clear();
        }


    }  // namespace visualizer

}  // namespace idealgas
