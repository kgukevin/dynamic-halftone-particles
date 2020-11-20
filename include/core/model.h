#pragma once

#include <map>
#include <string>
#include <utility>
#include <vector>

#include "cinder/gl/gl.h"
#include "particle.h"

namespace halftoneparticle {

class Model {
 private:
  glm::vec2 dimensions_;
  glm::vec2 origin_;
  std::vector<Particle> particles_;

  void HandleWallCollision(Particle &particle);

  void HandleParticleCollision(Particle &particle1, Particle &particle2);

  void EvaluateCollisions();

 public:
  Model(const glm::vec2 &origin, const glm::vec2 &dimensions)
      : origin_(origin), dimensions_(dimensions){};

  Model(const glm::vec2 &origin, const glm::vec2 &dimensions,
        std::vector<Particle> particles)
      : origin_(origin),
        dimensions_(dimensions),
        particles_(std::move(particles)){};

  std::vector<Particle> get_particles() const;

  /**
   * Add particle to model.
   * @param particle new particle to add
   */
  void AddParticle(const Particle &particle);

  /**
   * Creates particle with random direction with inputted velocity magnitude and
   * adds to model.
   * @param pos of new particle
   * @param vel_magnitude velocity magnitude of new particle
   * @param radius of new particle
   * @param mass
   * @param color
   */
  void CreateAndAddParticle(const glm::vec2 &pos, const float_t &vel_magnitude,
                            const float_t &radius, const float_t &mass,
                            const std::string &color);

  /**
   * Updates positions and velocities accordingly.
   */
  void UpdateMove();

  void UpdateRadii(const ci::Channel32f &img_channel);

  /**
   * Increases velocity of every particle by 20%.
   */
  void IncreaseVelocity();

  /**
   * Decreases velocity of every particle by 20%.
   */
  void DecreaseVelocity();

  /**
   * Packages model assets into assets usable by histogram.
   * @return assets for histogram to graph mapped from particle type(color) to
   * velocity assets
   */
  std::map<std::string, std::vector<float>> CreateVelHistogramData() const;

  /**
   * Clear model particles.
   */
  void Clear();
};

}  // namespace halftoneparticle