#include <cinder/app/AppBase.h>
#include <core/model.h>


namespace halftoneparticle {
    std::vector<Particle> Model::GetParticles() const {
        return particles_;
    }

    void Model::AddParticle(const Particle &particle) {
        particles_.push_back(particle);
    }

    void Model::CreateAndAddParticle(const glm::vec2 &pos,
                                     const float_t &vel_magnitude,
                                     const float_t &radius, const float_t &mass,
                                     const std::string &color) {
        // randomize direction with constant velocity using magnitude/direction form
        float_t vel_direction = ((float) rand() / RAND_MAX) * (360) + 0;

        // convert to cartesian velocities
        float_t vel_x = vel_magnitude * cos(vel_direction);
        float_t vel_y = vel_magnitude * sin(vel_direction);
        glm::vec2 new_velocity(vel_x, vel_y);

        Particle new_particle(pos, new_velocity, radius, mass, color);
        particles_.push_back(new_particle);
    }

    void Model::PreloadHalftoneImage(const glm::vec2 &top_left_corner, double particle_box_width, double particle_box_height, size_t x_increment, size_t y_increment, const std::string &color) {
        for (size_t x = 0; x < particle_box_width; x += x_increment) {
            for (size_t y = 0; y < particle_box_height; y += y_increment) {
                CreateAndAddParticle(top_left_corner + glm::vec2(x, y), 0, 1, 1, color);
            }
        }
    }

    void Model::UpdateMove() {
        EvaluateCollisions();
        for (Particle &particle : particles_) {
            particle.UpdatePosition();
        }
    }

    void Model::UpdateMovement() {
        for (Particle &particle : particles_) {
            particle.UpdatePosition();
            ApplyPerlinNoise(particle, particle.position(), .8f);
            particle.UpdateAcceleration(gravity_origin_, .2f);
            particle.UpdateVelocity();
        }
        EvaluateCollisions();

        DecreaseVelocity();
    }

    void Model::ApplyPerlinNoise(Particle &particle, const glm::vec2 &origin, float influence_factor) {
        float noise = perlin_.fBm(glm::vec3(origin * 0.009f, 0.1f));
        float angle = noise * 20.0f;

        particle.SetVelocity(particle.velocity() + influence_factor * glm::vec2(cos(angle), sin(angle)));
    }

    void Model::EvaluateCollisions() {
        //KDTree tree(particles_);
        for (Particle &particle : particles_) {
            HandleWallCollision(particle);
            //std::vector<Particle> neighborhood = tree.neighborhood(particle, particle.radius());
            //for (Particle &particle2 : neighborhood) {
            for (Particle &particle2 : particles_) {
                if (&particle != &particle2) {
                    if (glm::distance(particle.position(), particle2.position()) <=
                        particle.radius() + particle2.radius()) {
                        HandleParticleCollision(particle, particle2);
                    }
                }
            }
        }
    }

    void Model::HandleWallCollision(Particle &particle) {
        float_t radius = particle.radius();
        glm::vec2 pos = particle.position();
        glm::vec2 vel = particle.velocity();
        glm::vec2 outer_wall = origin_ + dimensions_;

        // checks particle boundaries and velocity direction
        if ((pos.x - radius <= origin_.x && vel.x < 0) ||
            (pos.x + radius >= outer_wall.x && vel.x > 0)) {
            vel.x *= -1;
        }
        if ((pos.y - radius <= origin_.y && vel.y < 0) ||
            (pos.y + radius >= outer_wall.y && vel.y > 0)) {
            vel.y *= -1;
        }
        particle.SetVelocity(vel);
    }

    void Model::HandleParticleCollision(Particle &particle, Particle &particle2) {
        glm::vec2 new_vel;
        glm::vec2 new_vel2;

        glm::vec2 pos = particle.position();
        glm::vec2 vel = particle.velocity();

        glm::vec2 pos2 = particle2.position();
        glm::vec2 vel2 = particle2.velocity();

        // new velocity 1 setup
        glm::vec2 delta_v1 = vel - vel2;
        glm::vec2 delta_x1 = pos - pos2;

        // new velocity 2 setup
        glm::vec2 delta_v2 = vel2 - vel;
        glm::vec2 delta_x2 = pos2 - pos;

        float_t mass_ratio_coefficient =
                2 * particle2.mass() / (particle.mass() + particle2.mass());
        float_t mass_ratio_coefficient2 =
                2 * particle.mass() / (particle.mass() + particle2.mass());

        if (glm::dot(delta_v1, delta_x1) < 0) {
            new_vel = vel - mass_ratio_coefficient * glm::dot(delta_v1, delta_x1) /
                                    pow(glm::length(delta_x1), 2) * delta_x1;
            new_vel2 = vel2 - mass_ratio_coefficient2 * glm::dot(delta_v2, delta_x2) /
                                      pow(glm::length(delta_x2), 2) * delta_x2;
            particle.SetVelocity(new_vel);
            particle2.SetVelocity(new_vel2);
        }
    }

    void Model::SetGravityOrigin(const glm::vec2 &gravity_origin) {
        gravity_origin_ = gravity_origin;
    }

    void Model::IncreaseVelocity() {
        for (Particle &particle : particles_) {
            particle.SetVelocity(
                    glm::vec2(particle.velocity().x * 1.2, particle.velocity().y * 1.2));
        }
    }

    void Model::DecreaseVelocity() {
        for (Particle &particle : particles_) {
            particle.SetVelocity(
                    glm::vec2(particle.velocity().x * .8, particle.velocity().y * .8));
        }
    }

    void Model::Clear() {
        particles_.clear();
    }

}// namespace halftoneparticle