#include <core/particle.h>
#include <fstream>

namespace halftoneparticle {

    const glm::vec2 Particle::position() const {
        return position_;
    }

    const glm::vec2 Particle::velocity() const {
        return velocity_;
    }

    const float Particle::GetVelocityMagn() const {
        return sqrt(pow(velocity_.x, 2) + pow(velocity_.y, 2));
    }

    const int Particle::age() const {
        return age_;
    }

    const float_t Particle::radius() const {
        return radius_;
    }

    const float_t Particle::mass() const {
        return mass_;
    }

    const std::string Particle::color() const {
        return color_;
    }

    void Particle::UpdatePosition() {
        position_ += velocity_;
        age_++;
    }

    void Particle::UpdateVelocity() {

        velocity_ += acceleration_;
    }

    void Particle::UpdateAcceleration(const glm::vec2 &g_origin) {
        glm::vec2 displacement = position_ - g_origin;
        float distance = sqrt(pow(displacement.x, 2) + pow(displacement.y, 2));
        acceleration_.x = -.2f * displacement.x / distance;
        acceleration_.y = -.2f * displacement.y / distance;
    }

    void Particle::set_velocity(const glm::vec2 &velocity) {
        velocity_ = velocity;
    }

    void Particle::SetRadius(const float_t &radius) {
        radius_ = radius;
    }

}  // namespace halftoneparticle