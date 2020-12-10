#include <core/particle.h>
#include <fstream>


namespace halftoneparticle {
    Particle::Particle() = default;

    const glm::vec2 Particle::position() const {
        return position_;
    }

    const glm::vec2 Particle::velocity() const {
        return velocity_;
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

    void Particle::UpdateAcceleration(const glm::vec2 &g_origin, float influence_factor) {
        glm::vec2 displacement = position_ - g_origin;
        float distance = glm::distance(position_, g_origin);//sqrt(pow(displacement.x, 2) + pow(displacement.y, 2));
        acceleration_.x = -influence_factor * displacement.x / distance;
        acceleration_.y = -influence_factor * displacement.y / distance;
    }

    void Particle::SetVelocity(const glm::vec2 &velocity) {
        velocity_ = velocity;
    }

    void Particle::SetAge(int age) {
        age_ = age;
    }

}// namespace halftoneparticle