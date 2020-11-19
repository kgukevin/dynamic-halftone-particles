
#include <core/model.h>
#include <visualizer/histogram_box.h>

namespace idealgas {

namespace visualizer {

using glm::vec2;

HistogramBox::HistogramBox(const vec2& top_left_corner,
                           double histogram_box_width,
                           double histogram_box_height, double histogram_margin)
    : top_left_corner_(top_left_corner),
      histogram_box_height_(histogram_box_height),
      histogram_box_width_(histogram_box_width),
      histogram_margin_(histogram_margin) {
}

void HistogramBox::Draw() const {
  // draws container box around whole histogram_box
  ci::gl::color(ci::Color("white"));
  vec2 bottom_right_corner =
      top_left_corner_ + vec2(histogram_box_width_, histogram_box_height_);
  ci::Rectf pixel_bounding_box(top_left_corner_, bottom_right_corner);
  ci::gl::drawStrokedRect(pixel_bounding_box);

  // draw process for individual histograms stored
  for (size_t index = 0; index < histograms_.size(); index++) {
    // draws container box around individual histogram
    ci::gl::color(ci::Color("white"));
    vec2 histogram_top_left_corner =
        top_left_corner_ + vec2(0, index * histogram_height_);
    bottom_right_corner = histogram_top_left_corner +
                          vec2(histogram_box_width_, histogram_height_);
    pixel_bounding_box =
        ci::Rectf(histogram_top_left_corner, bottom_right_corner);
    ci::gl::drawStrokedRect(pixel_bounding_box);

    // draws in y-axis labels
    ci::gl::color(ci::Color("white"));
    for (size_t y_axis_tick = 0; y_axis_tick <= histograms_[index].maxYValue();
         y_axis_tick++) {
      ci::gl::drawString(
          std::to_string(y_axis_tick),
          vec2(histogram_top_left_corner.x + histogram_margin_ - 10,
               histogram_top_left_corner.y +
                   (histogram_height_ - histogram_margin_) -
                   static_cast<float>(y_axis_tick) /
                       histograms_[index].maxYValue() *
                       (histogram_height_ - 2 * histogram_margin_)));
    }

    // calculates initial coordinates to create bins
    size_t bins = histograms_[index].bins();
    auto bin_length = static_cast<float_t>((histogram_width_) / bins);
    vec2 bin_top_left_corner;
    vec2 bin_bottom_left_corner =
        histogram_top_left_corner +
        vec2(histogram_margin_, histogram_height_ - histogram_margin_);
    vec2 bin_bottom_right_corner = bin_bottom_left_corner;

    size_t bin_count = 0;  // for x-axis label placement
    for (const auto& kv : histograms_[index].data()) {
      // draws x-axis labels
      if (bin_count % 5 == 0) {
        ci::gl::drawString(std::to_string(kv.first).substr(
                               0, std::to_string(kv.first).find('.') + 3),
                           bin_bottom_left_corner);
      }
      bin_count++;

      // draws bins
      std::string color = histograms_[index].type();
      const char* svgkey = color.c_str();
      // convert char* svg key (color name) to rgb values
      ci::gl::color(ci::Color(ci::svgNameToRgb(svgkey)));
      double bin_height =
          (static_cast<float>(kv.second) / histograms_[index].maxYValue()) *
          (histogram_height_ - 2 * histogram_margin_);
      bin_top_left_corner =
          vec2(bin_bottom_left_corner.x, bin_bottom_left_corner.y - bin_height);

      bin_bottom_right_corner += vec2(bin_length, 0);

      pixel_bounding_box =
          ci::Rectf(bin_top_left_corner, bin_bottom_right_corner);
      ci::gl::drawStrokedRect(pixel_bounding_box);
      bin_top_left_corner += vec2(bin_length, 0);
      bin_bottom_left_corner += vec2(bin_length, 0);
    }
  }
}

void HistogramBox::InputData(
    const std::map<std::string, std::vector<float>>& data) {
  histograms_.clear();
  for (const auto& kv : data) {
    histograms_.emplace_back(kv.first, 20, kv.second);
  }
  histogram_height_ = histogram_box_height_ / histograms_.size();
}

}  // namespace visualizer

}  // namespace idealgas
