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

#ifndef LIGHTSHOW_SOLIDCOLORPRESET_H
#define LIGHTSHOW_SOLIDCOLORPRESET_H

#include <memory>

#include "Preset.h"

namespace LightShow {

/**
 * display a solid color
 */
class SolidColorPreset : public Preset {
 public:
  /**
   * Create a current_preset that displays a solid a color
   * @param controller
   * @param r
   * @param g
   * @param b
   * @param interval
   */
  explicit SolidColorPreset(std::shared_ptr<Controller> controller,
                            uint8_t r = 0xFF, uint8_t g = 0xFF,
                            uint8_t b = 0xFF);

  /**
   * Perform one loop
   * @return 0 on success or a LightShow::Error on error
   */
  Error Start() override;

 protected:
  /// controller that will be used to set LEDs
  std::shared_ptr<Controller> controller_;

  /// red byte of the color to cycle
  uint8_t r_;

  /// green byte of the color to cycle
  uint8_t g_;

  /// blue byte of the color to cycle
  uint8_t b_;
};

}  // namespace LightShow

#endif  // LIGHTSHOW_SOLIDCOLORPRESET_H
