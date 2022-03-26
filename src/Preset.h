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

#ifndef LIGHTSHOW_PRESET_H
#define LIGHTSHOW_PRESET_H

#include "Controller.h"
#include "Error.h"

namespace LightShow {

/**
 * a base LightShow current_preset that includes no instructions
 */
class Preset {
 public:
  /**
   * Create a current_preset that does nothing
   * @param controller the controller_ that handles LED updates
   */
  Preset() = default;

  /**
   * Start this current_preset
   * @return 0 on success or a LightShow::Error on error
   */
  virtual Error Start() { return NoError; }

  /**
   * Perform one loop
   * @return 0 on success or a LightShow::Error on error
   */
  virtual Error Loop() { return NoError; }
};

}  // namespace LightShow

#endif  // LIGHTSHOW_PRESET_H
