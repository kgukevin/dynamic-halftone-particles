#include <core/particle.h>

#include <fstream>

namespace idealgas {

const glm::vec2 Particle::position() const {
  return position_;
}

const glm::vec2 Particle::velocity() const {
  return velocity_;
}

const float Particle::GetVelocityMagn() const {
  return sqrt(pow(velocity_.x, 2) + pow(velocity_.y, 2));
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
}

void Particle::set_velocity(const glm::vec2 &velocity) {
  velocity_ = velocity;
}

}  // namespace idealgas