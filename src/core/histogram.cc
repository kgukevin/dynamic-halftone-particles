#include <core/histogram.h>

#include <fstream>
#include <utility>

namespace idealgas {

Histogram::Histogram(const std::string& type, const size_t& bins, const std::vector<float>& data)
    : type_(type), bins_(bins) {
  FillBins(data);
}

const std::string Histogram::type() const {
  return type_;
}

const size_t Histogram::bins() const {
  return bins_;
}

const size_t Histogram::maxYValue() const {
  return max_y_val_;
}

const std::map<float, size_t> Histogram::data() const {
  return data_;
}

void Histogram::FillBins(std::vector<float> data) {
  std::sort(data.begin(), data.end());

  max_x_val_ = data[data.size() - 1];

  float_t bin_range = (max_x_val_) / (static_cast<float>(bins_));

  float_t max_bin_val = max_x_val_ + 2 * bin_range;

  bin_range = floorf(max_bin_val / bins_ * 10000) / 10000;

  // fill empty bins
  for (float bin = 0; bin < max_bin_val; bin += bin_range) {
    float rounded_bin = floorf(bin * 10000) / 10000;
    data_[rounded_bin] = 0;
  }

  auto start = data_.begin();
  for (float vel : data) {
    for (auto iter = start; iter != data_.end(); ++iter) {
      float k = iter->first;
      if (vel < k) {
        auto itr = --iter;
        data_[itr->first] += 1;
        start = itr;
        break;
      }
    }
  }

  max_y_val_ = FindHighestFreq();
}

size_t Histogram::FindHighestFreq() {
  size_t highest_freq = 0;
  for (const auto& kv : data_) {
    if (kv.second > highest_freq) {
      highest_freq = kv.second;
    }
  }
  return highest_freq;
}

}  // namespace idealgas