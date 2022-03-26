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

#ifndef LIGHTSHOW_CONTROLLER_H
#define LIGHTSHOW_CONTROLLER_H

#include <Arduino.h>

#include "Error.h"
#include "LightShow.h"
#include "Preset.h"

namespace LightShow {

class Controller {
 public:
  /**
   * Stop the currently running show.
   * @return 0 on success or a LightShow::Error on error
   */
  virtual Error Stop();

  /**
   * Stop the currently running show.
   * @param fade_ms the approximate number of milliseconds over which to fade
   * out the show
   * @return 0 on success or a LightShow::Error on error
   */
  Error Stop(uint32_t fade_ms);

  /**
   * Start a scene
   * @param preset the current_preset index of the scene to Start (0-indexed)
   * @return 0 on success or a LightShow::Error on error
   */
  virtual Error Start(int preset);

  /**
   * return how many presets are currently configured
   * If this is 0, then no shows can be started.
   * @return the number of configured presets
   */
  virtual int GetPresetCount();

  /**
   * Fade to a color
   * This is a blocking operation.
   * @param fade_ms the approximate number of milliseconds over which to fade
   * @param r Red brightness, 0 to 255.
   * @param g Green brightness, 0 to 255.
   * @param b Blue brightness, 0 to 255.
   * @return 0 on success or a LightShow::Error on error
   */
  virtual Error Fade(uint32_t fade_ms, uint8_t r, uint8_t g, uint8_t b) = 0;

  /**
   * Set all LEDs to a color
   * @param r Red brightness, 0 to 255.
   * @param g Green brightness, 0 to 255.
   * @param b Blue brightness, 0 to 255.
   * @return 0 on success or a LightShow::Error on error
   */
  virtual Error SetLEDs(uint8_t r, uint8_t g, uint8_t b) = 0;

  /**
   * Set a single LED to a color
   * @param i the index of the LED to set (0-indexed)
   * @param r Red brightness, 0 to 255.
   * @param g Green brightness, 0 to 255.
   * @param b Blue brightness, 0 to 255.
   * @return 0 on success or a LightShow::Error on error
   */
  virtual Error SetLED(uint32_t i, uint8_t r, uint8_t g, uint8_t b) = 0;

  /**
   * reads the local pixel values and pushing them to the NeoPixel
   * @return 0 on success or a LightShow::Error on error
   */
  virtual Error Update() = 0;
};

}  // namespace LightShow

#endif  // LIGHTSHOW_CONTROLLER_H
