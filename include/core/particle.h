#pragma once

#include <map>
#include <string>
#include <vector>

#include "cinder/gl/gl.h"

namespace halftoneparticle {

class Particle {
 private:
  std::string color_;
  float_t mass_;
  float_t radius_;
  glm::vec2 position_;
  glm::vec2 velocity_;
  glm::vec2 acceleration_;

 public:
  Particle(const glm::vec2 &position, const glm::vec2 &velocity,
           const float_t &radius)
      : position_(position), velocity_(velocity), radius_(radius){};

  Particle(const glm::vec2 &position, const glm::vec2 &velocity,
           const float_t &radius, const float_t &mass, const std::string &color)
      : position_(position),
        velocity_(velocity),
        radius_(radius),
        mass_(mass),
        color_(color){};

  const glm::vec2 position() const;

  const glm::vec2 velocity() const;

  /**
   * Calculates velocity magnitude.
   * @return velocity magnitude
   */
  const float GetVelocityMagn() const;

  const float_t radius() const;

  const float_t mass() const;

  const std::string color() const;

  void set_velocity(const glm::vec2 &velocity);

  void SetRadius(const float_t &radius);

  /**
   * Updates postition using velocity by one increment of time.
   */
  void UpdatePosition();

  void UpdateVelocity();

    void UpdateAcceleration(const glm::vec2 &g_origin);
};

}  // namespace halftoneparticle