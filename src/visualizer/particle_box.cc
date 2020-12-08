
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

            for (size_t x = 0; x < particle_box_width; x += 20) {
                for (size_t y = 0; y < particle_box_height; y += 20) {
                    model_.CreateAndAddParticle(top_left_corner + vec2(x, y), 0, 1, 1, "white");
                }
            }

        }

        ParticleBox::ParticleBox(const glm::vec2 &top_left_corner, double particle_box_width,
                                 double particle_box_height, const ci::Channel32f &channel)
                : model_(top_left_corner, vec2(particle_box_width, particle_box_height)),
                  top_left_corner_(top_left_corner),
                  particle_box_height_(particle_box_height),
                  particle_box_width_(particle_box_width),
                  img_channel_(std::move(channel)) {

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
                ci::gl::drawSolidCircle(particle.position(), (img_channel_.getValue(particle.position())) * 6.0f);
            }
        }

        void ParticleBox::Update() {
            model_.UpdateMove();
            //model_.UpdateRadii(img_channel_);
        }

        void ParticleBox::HandleBrush(const vec2 &brush_screen_coords) {
            if (IsWithinWalls(brush_screen_coords)) {

                model_.SetGravityOrigin(brush_screen_coords);

//                if (particle_types_[current_particle_index_] == "darkorange") {
//                    model_.CreateAndAddParticle(brush_screen_coords, 4, 7, 5, "darkorange");
//                }
//                if (particle_types_[current_particle_index_] == "cyan") {
//                    model_.CreateAndAddParticle(brush_screen_coords, 6, 4, 3, "cyan");
//                }
//                if (particle_types_[current_particle_index_] == "deeppink") {
//                    model_.CreateAndAddParticle(brush_screen_coords, 1, 10, 7, "deeppink");
//                }
//                if (particle_types_[current_particle_index_] == "mediumspringgreen") {
//                    model_.CreateAndAddParticle(brush_screen_coords, 2, 5, 4.5, "mediumspringgreen");
//                }

                for (int num = 0; num < 10; num++) {
                    model_.CreateAndAddParticle(brush_screen_coords, 1, 9, 1, particle_types_[current_particle_index_]);
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

        const std::string &ParticleBox::GetCurrentParticleType() {
            return particle_types_[current_particle_index_];
        }

        void ParticleBox::IncrementParticleTypeIndex() {
            current_particle_index_++;
            if (current_particle_index_ == particle_types_.size()) {
                current_particle_index_ = 0;
            }
        }

        void ParticleBox::LoadImage(const ci::Channel32f &img_channel) {
            img_channel_ = img_channel;
        }

        void ParticleBox::Clear() {
            // TODO: implement this method
            model_.Clear();
        }


    }  // namespace visualizer

}  // namespace halftoneparticle
