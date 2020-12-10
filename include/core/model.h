#pragma once

#include <map>
#include <string>
#include <utility>
#include <vector>

#include "KDTree.hpp"
#include "cinder/Perlin.h"
#include "cinder/gl/gl.h"
#include "particle.h"

namespace halftoneparticle {

    class Model {
    private:
        glm::vec2 dimensions_;
        glm::vec2 origin_;
        std::vector<Particle> particles_;
        glm::vec2 gravity_origin_ = origin_ + 0.5f * dimensions_;

        cinder::Perlin perlin_ = cinder::Perlin();

        void HandleWallCollision(Particle &particle);

        void HandleParticleCollision(Particle &particle1, Particle &particle2);

        void EvaluateCollisions();

    public:
        Model(const glm::vec2 &origin, const glm::vec2 &dimensions)
            : origin_(origin), dimensions_(dimensions){};

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
         * Preloads particles to draw halftone image.
         * @param top_left_corner of particle_box
         * @param particle_box_width
         * @param particle_box_height
         * @param x_increment horizantal pixel distance between particles
         * @param y_increment vertical pixel distance between particles
         * @param color of particles
         */
        void PreLoadHalftoneImage(const glm::vec2 &top_left_corner, double particle_box_width, double particle_box_height, size_t x_increment, size_t y_increment, const std::string &color);

        /**
         * Updates positions and velocities accordingly.
         */
        void UpdateMovement();

        /**
         * Applies perlin noise to particle velocity.
         * @param particle
         * @param origin of perlin noise influence
         * @param influence_factor multiplies as magnitude of noise vector
         */
        void ApplyPerlinNoise(Particle &particle, const glm::vec2 &origin, float influence_factor);

        /**
         * Updates position of center of gravity.
         * @param gravity_origin
         */
        void SetGravityOrigin(const glm::vec2 &gravity_origin);

        /**
         * Increases velocity of every particle by 20%.
         */
        void IncreaseVelocity();

        /**
         * Decreases velocity of every particle by 20%.
         */
        void DecreaseVelocity();

        /**
         * Clear model particles.
         */
        void Clear();
    };

}// namespace halftoneparticle