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
        int age_;

    public:
        Particle();

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

        const int age() const;

        const float_t radius() const;

        const float_t mass() const;

        const std::string color() const;

        void SetVelocity(const glm::vec2 &velocity);

        void SetAge(int age);

        /**
         * Updates position using velocity by one increment of time.
         */
        void UpdatePosition();

        /**
         * Updates velocity using acceleration by one increment of time.
         */
        void UpdateVelocity();

        /**
         * Updates acceleration due to gravity.
         * @param g_origin origin of gravity
         * @param influence_factor multiplies as magnitude of gravity vector
         */
        void UpdateAcceleration(const glm::vec2 &g_origin, float influence_factor);
    };

}// namespace halftoneparticle