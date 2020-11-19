#pragma once

#include <core/histogram.h>
#include <core/model.h>

#include "cinder/gl/gl.h"

namespace idealgas {

namespace visualizer {

/**
 * A histogram_box which will be displayed in the Cinder application and update
 * based on number of particle types and their respective histogram velocity
 * assets distribution.
 */
class HistogramBox {
 public:
  /**
   * Creates histogram_box.
   * @param top_left_corner is origin of histogram_box
   * @param histogram_box_width width dimension of histogram_box
   * @param histogram_box_height height dimension of histogram_box
   */
  HistogramBox(const glm::vec2& top_left_corner, double histogram_box_width,
               double histogram_box_height, double histogram_margin);

  /**
   * Displays the current state of the histogram_box in the Cinder application.
   */
  void Draw() const;

  /**
   * Inputs assets to create histograms and display.
   * @param data to create histograms from
   */
  void InputData(const std::map<std::string, std::vector<float>>& data);

 private:
  glm::vec2 top_left_corner_;

  double histogram_box_height_;

  double histogram_box_width_;

  double histogram_margin_;

  double histogram_height_;

  double histogram_width_ = histogram_box_width_ - 2 * histogram_margin_;

  std::vector<Histogram> histograms_;


};

}  // namespace visualizer

}  // namespace idealgas
