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

#ifndef LIGHTSHOW_FLASHCOLORPRESET_H
#define LIGHTSHOW_FLASHCOLORPRESET_H

#include <memory>

#include "Preset.h"

namespace LightShow {

/**
 * flash a color
 */
class FlashColorPreset : public Preset {
 public:
  /**
   * Create a preset that flashes a color
   * @param controller the controller used to set LEDs
   * @param r red 0-255
   * @param g green 0-255
   * @param b blue 0-255
   * @param interval the number of loop cycles between flashes
   */
  explicit FlashColorPreset(std::shared_ptr<Controller> controller,
                            uint8_t r = 0xFF, uint8_t g = 0xFF,
                            uint8_t b = 0xFF, uint32_t interval = 1);

  /**
   * Perform one loop
   * @return 0 on success or a LightShow::Error on error
   */
  Error Loop() override;

 protected:
  /// controller that will be used to set LEDs
  std::shared_ptr<Controller> controller_;

  /// red byte of the color to cycle
  uint8_t r_;

  /// green byte of the color to cycle
  uint8_t g_;

  /// blue byte of the color to cycle
  uint8_t b_;

  /// true if we are currently showing_ the target color, else false
  bool showing_ = true;

  /// how many times have we looped since the last flip?
  uint32_t loop_count_ = 0;

  /// how many loop cycles to skip before flipping
  uint32_t interval_;
};

}  // namespace LightShow

#endif  // LIGHTSHOW_FLASHCOLORPRESET_H
