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

#include "FastLEDController.h"

#if LIGHTSHOW_FASTLED_ENABLE == 1

namespace LightShow {

FastLEDController::FastLEDController(uint32_t num) {
  this->num_leds_ = num;
  this->leds_ = new CRGB[num]{0};
  this->controller_ = &FastLED.addLeds<NEOPIXEL, LIGHTSHOW_FASTLED_DATA_PIN>(
      this->leds_, static_cast<int>(num));
}

FastLEDController::~FastLEDController() { this->Stop(); }

Error FastLEDController::Fade(uint32_t fade_ms, CRGB c) {
  const auto start_time = millis();
  auto now = start_time;

  CRGB *orig = new CRGB[this->num_leds_];
  memcpy(orig, this->leds_, this->num_leds_ * sizeof(CRGB));

  // progressively inch the neopixel_ strip closer to the target value
  do {
    // determine the percentage of progress made across fade_ms 0.0-1.0
    auto scale =
        static_cast<float>(now - start_time) / static_cast<float>(fade_ms);

    // for each pixel, set it to some approximate value between starting and
    // ending values in proportion to the calculated scale
    for (uint32_t i = 0; i < this->num_leds_; i++) {
      this->SetLED(
          i,
          orig[i].r + (uint8_t)((static_cast<float>(c.r - orig[i].r) * scale)),
          orig[i].g + (uint8_t)((static_cast<float>(c.g - orig[i].g) * scale)),
          orig[i].b + (uint8_t)((static_cast<float>(c.b - orig[i].b) * scale)));
    }
    this->Update();

    // recalculate the current time, and keep going until we hit our target
    // fade_ms
  } while ((now = millis()) < start_time + fade_ms);

  // update our local neopixel_ definitions and perform a final update
  this->SetLEDs(c.r, c.g, c.b);
  this->Update();
  return NoError;
}

Error FastLEDController::Update() {
  this->controller_->showLeds();
  return NoError;
}

Error FastLEDController::Fade(uint32_t fade_ms, uint8_t r, uint8_t g,
                              uint8_t b) {
  return this->Fade(fade_ms, CRGB(r, g, b));
}

Error FastLEDController::SetLEDs(uint8_t r, uint8_t g, uint8_t b) {
  for (uint32_t i = 0; i < this->num_leds_; i++) {
    this->leds_[i].r = r;
    this->leds_[i].g = g;
    this->leds_[i].b = b;
  }
  return NoError;
}

Error FastLEDController::SetLED(uint32_t i, uint8_t r, uint8_t g, uint8_t b) {
  if (i > this->num_leds_) {
    return LEDIndexOutOfRange;
  }
  this->leds_[i].r = r;
  this->leds_[i].g = g;
  this->leds_[i].b = b;
  return NoError;
}

}  // namespace LightShow

#endif  // LIGHTSHOW_FASTLED_ENABLE
