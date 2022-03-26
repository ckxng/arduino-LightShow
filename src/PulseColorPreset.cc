// MIT License
//
// Copyright (c) 2022 Cameron King
//
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation files
// (the "Software"), to deal in the Software without restriction,
// including without limitation the rights to use, copy, modify, merge,
// publish, distribute, sublicense, and/or sell copies of the Software,
// and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
// BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
/// @file

#include "PulseColorPreset.h"

#include <utility>

namespace LightShow {

PulseColorPreset::PulseColorPreset(std::shared_ptr<Controller> controller,
                                   uint8_t r, uint8_t g, uint8_t b,
                                   uint32_t interval, uint32_t steps)
    : controller_(std::move(controller)),
      r_(r),
      g_(g),
      b_(b),
      interval_(interval),
      steps_(steps) {}

Error PulseColorPreset::Loop() {
  // skip this cycle if it's not time to color change yet
  if (++this->loop_count_ < this->interval_) {
    return NoError;
  }

  // it's time to color change, reset the counter
  this->loop_count_ = 0;

  // switch directions if needed
  if (this->steps_taken_ >= this->steps_) {
    this->advancing_ = false;
  } else if (this->steps_taken_ == 0) {
    this->advancing_ = true;
  }

  // update LEDs
  this->controller_->SetLEDs(
      static_cast<uint8_t>((static_cast<float>(this->steps_taken_) /
                            static_cast<float>(this->steps_)) *
                           static_cast<float>(this->r_)),
      static_cast<uint8_t>((static_cast<float>(this->steps_taken_) /
                            static_cast<float>(this->steps_)) *
                           static_cast<float>(this->g_)),
      static_cast<uint8_t>((static_cast<float>(this->steps_taken_) /
                            static_cast<float>(this->steps_)) *
                           static_cast<float>(this->b_)));
  this->controller_->Update();

  // take another step
  if (this->advancing_) {
    this->steps_taken_++;
  } else {
    this->steps_taken_--;
  }

  return NoError;
}

}  // namespace LightShow
