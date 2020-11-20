#pragma once

#include <core/model.h>

#include "cinder/gl/gl.h"

namespace halftoneparticle {

namespace visualizer {

/**
 * A particle_box which will be displayed in the Cinder application and respond
 * to mouse events.
 */
class ParticleBox {
 public:
  /**
   * Creates particle_box.
   * @param top_left_corner is origin of particle_box
   * @param particle_box_width width dimension of particle_box
   * @param particle_box_height height dimension of particle_box
   */
  ParticleBox(const glm::vec2 &top_left_corner, double particle_box_width,
              double particle_box_height);

  ParticleBox(const glm::vec2 &top_left_corner, double particle_box_width,
                double particle_box_height, const ci::Channel32f &channel);

  /**
   * Displays the current state of the particle_box in the Cinder application.
   */
  void Draw() const;

  /**
   * Calls model update.
   */
  void Update();

  /**
   * Adds a particle to coordinates if they are within bounds of the box.
   *
   * @param brush_screen_coords the screen coordinates at which the brush is
   *           located
   */
  void HandleBrush(const glm::vec2 &brush_screen_coords);

  /**
   * Checks if new particle to be added is within borders of particle_box.
   * @param brush_screen_coords
   * @return True if new particle is within walls, otherwise false.
   */
  bool IsWithinWalls(const glm::vec2 &brush_screen_coords);

  /**
   * Accessor method for the model.
   * @return reference of model
   */
  Model &GetModel();

  /**
   * Gets particle type (classified by color).
   * @return string (svgname) of current particle type
   */
  const std::string GetCurrentParticleType();

  /**
   * Increments particle type index through particle types array. Wraps back to
   * 0 when reach array length.
   */
  void IncrementParticleTypeIndex();

  void LoadImage(const ci::Channel32f &img_channel);

  /**
   * Set all of the particle_box pixels to an unshaded state.
   */
  void Clear();

 private:
  glm::vec2 top_left_corner_;

  double particle_box_height_;

  double particle_box_width_;

  Model model_;

  ci::Channel32f img_channel_;

  /**
   * Current particle type index.
   */
  size_t current_particle_index_ = 0;

  /**
   * Preset particle types.
   */
  std::array<std::string, 4> particle_types_ = {
      "darkorange",
      "cyan",
      "deeppink",
      "mediumspringgreen"};
};

}  // namespace visualizer

}  // namespace halftoneparticle
