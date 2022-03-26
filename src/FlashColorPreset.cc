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

#include "FlashColorPreset.h"

#include <utility>

namespace LightShow {

FlashColorPreset::FlashColorPreset(std::shared_ptr<Controller> controller,
                                   uint8_t r, uint8_t g, uint8_t b,
                                   uint32_t interval)
    : controller_(std::move(controller)),
      r_(r),
      g_(g),
      b_(b),
      interval_(interval) {}

Error FlashColorPreset::Loop() {
  // skip this cycle if it's not time to flash yet
  if (++this->loop_count_ < this->interval_) {
    return NoError;
  }

  // it's time to flash, reset the counter
  this->loop_count_ = 0;

  // currently showing, time to disable
  if (this->showing_) {
    this->controller_->SetLEDs(0, 0, 0);
    this->showing_ = false;
  } else {
    this->controller_->SetLEDs(this->r_, this->g_, this->b_);
    this->showing_ = true;
  }
  this->controller_->Update();

  return NoError;
}

}  // namespace LightShow
