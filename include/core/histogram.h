#pragma once

#include <map>
#include <string>
#include <vector>

#include "cinder/gl/gl.h"

namespace idealgas {

class Histogram {
 private:
  std::string type_;

  size_t bins_;

  float max_x_val_;

  size_t max_y_val_;

  std::map<float, size_t> data_;

  /**
   * Finds highest frequency or greatest y-value from map.
   * @return highest frequency for velocities
   */
  size_t FindHighestFreq();

 public:
  Histogram(const std::string& type, const size_t& bins, const std::vector<float>& data);

  const std::string type() const;

  const size_t bins() const;

  const size_t maxYValue() const;

  const std::map<float, size_t> data() const;

  /**
   * Calculates frequencies and fills bins to display.
   * @param data velocities for particle types
   */
  void FillBins(std::vector<float> data);
};

}  // namespace idealgas