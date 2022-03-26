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

#include "NeoPixelController.h"

#if LIGHTSHOW_NEOPIXEL_ENABLE == 1

namespace LightShow {

NeoPixelController::NeoPixelController(uint16_t n, int16_t pin,
                                       neoPixelType type)
    : num_pixels_(n) {
  this->neopixel_ = std::unique_ptr<Adafruit_NeoPixel>(
      new Adafruit_NeoPixel(this->num_pixels_, pin, type));
  this->pixels_ = std::vector<SingleNeoPixel>(n);
  this->neopixel_->begin();
}

NeoPixelController::~NeoPixelController() { this->Stop(0); }

Error NeoPixelController::Fade(uint32_t fade_ms, uint32_t c) {
  return this->Fade(fade_ms,
                    static_cast<uint8_t>((c & 0xFF0000) >> 16),     // r
                    static_cast<uint8_t>((c & 0xFF0000) >> 16),     // g
                    static_cast<uint8_t>((c & 0xFF0000) >> 8),      // b
                    static_cast<uint8_t>((c & 0xFF000000) >> 24));  // w
}

Error NeoPixelController::Fade(uint32_t fade_ms, SingleNeoPixel p) {
  return this->Fade(fade_ms, p.r, p.g, p.b, p.w);
}

Error NeoPixelController::Fade(uint32_t fade_ms, uint8_t r, uint8_t g,
                               uint8_t b, uint8_t w) {
  const auto start_time = millis();
  auto now = start_time;

  // progressively inch the neopixel_ strip closer to the target value
  do {
    // determine the percentage of progress made across fade_ms 0.0-1.0
    auto scale =
        static_cast<float>(now - start_time) / static_cast<float>(fade_ms);

    // for each pixel, set it to some approximate value between starting and
    // ending values in proportion to the calculated scale
    for (uint32_t i = 0; i < this->num_pixels_; i++) {
      // don't use SetLED, as we are calculating the difference in-place and
      // will update that at the end
      this->neopixel_->setPixelColor(
          i,
          this->pixels_[i].r +
              static_cast<uint8_t>(
                  (static_cast<float>(r - this->pixels_[i].r) * scale)),
          this->pixels_[i].g +
              static_cast<uint8_t>(
                  (static_cast<float>(g - this->pixels_[i].g) * scale)),
          this->pixels_[i].b +
              static_cast<uint8_t>(
                  (static_cast<float>(b - this->pixels_[i].b) * scale)),
          this->pixels_[i].w +
              static_cast<uint8_t>(
                  (static_cast<float>(w - this->pixels_[i].w) * scale)));
    }
    this->neopixel_->show();

    // recalculate the current time, and keep going until we hit our target
    // fade_ms
  } while ((now = millis()) < start_time + fade_ms);

  // update our local neopixel_ definitions and perform a final update
  this->SetLEDs(r, g, b, w);
  this->Update();

  return NoError;
}

Error NeoPixelController::Update() {
  for (auto i = 0; i < this->neopixel_->numPixels(); i++) {
    this->neopixel_->setPixelColor(i, this->pixels_[i].c);
  }
  this->neopixel_->show();

  return NoError;
}

Error NeoPixelController::Fade(uint32_t fade_ms, uint8_t r, uint8_t g,
                               uint8_t b) {
  return this->Fade(fade_ms, r, g, b, 0);
}

Error NeoPixelController::SetLEDs(uint8_t r, uint8_t g, uint8_t b) {
  for (auto &item : this->pixels_) {
    item.r = r;
    item.g = g;
    item.b = b;
    item.w = 0x00;
  }
  return NoError;
}

Error NeoPixelController::SetLED(uint32_t i, uint8_t r, uint8_t g, uint8_t b) {
  if (i > this->num_pixels_) {
    return LEDIndexOutOfRange;
  }
  this->pixels_[i].r = r;
  this->pixels_[i].g = g;
  this->pixels_[i].b = b;
  this->pixels_[i].w = 0x00;
  return NoError;
}

Error NeoPixelController::SetLEDs(uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
  for (auto &item : this->pixels_) {
    item.r = r;
    item.g = g;
    item.b = b;
    item.w = w;
  }
  return NoError;
}

Error NeoPixelController::SetLED(uint32_t i, uint8_t r, uint8_t g, uint8_t b,
                                 uint8_t w) {
  if (i > this->num_pixels_) {
    return LEDIndexOutOfRange;
  }
  this->pixels_[i].r = r;
  this->pixels_[i].g = g;
  this->pixels_[i].b = b;
  this->pixels_[i].w = w;
  return NoError;
}

}  // namespace LightShow

#endif  // LIGHTSHOW_NEOPIXEL_ENABLE
