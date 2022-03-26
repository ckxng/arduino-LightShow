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

#ifndef LIGHTSHOW_NEOPIXELCONTROLLER_H
#define LIGHTSHOW_NEOPIXELCONTROLLER_H

#include "Controller.h"

#if LIGHTSHOW_NEOPIXEL_ENABLE == 1

#include <Arduino.h>

#include <memory>
#include <vector>

#include "Adafruit_NeoPixel.h"

namespace LightShow {

/**
 * a single pixel in NeoPixel format
 *
 * used for representing NeoPixel data in a convenient way to reduce
 * inconvenient bitshifting operations and make it easier to operate on
 * individual pixel colors
 */
union SingleNeoPixel {
  struct {
    /// wrgb format (0xWWRRGGBB)
    // cppcheck-suppress unusedStructMember
    //   cppcheck does not correctly detect struct member usage via. arrays,
    //   therefore generating a false warning
    uint32_t c;
  };
  struct {
    /// blue 0-255
    // cppcheck-suppress unusedStructMember
    uint8_t b;
    /// green 0-255
    // cppcheck-suppress unusedStructMember
    uint8_t g;
    /// red 0-255
    // cppcheck-suppress unusedStructMember
    uint8_t r;
    /// white 0-255
    // cppcheck-suppress unusedStructMember
    uint8_t w;
  };
};

class NeoPixelController : public Controller {
 public:
  /**
   * Create NeoPixel-based Controller by initializing a new NeoPixel
   * object. The NeoPixel strip will be created and begin() will be called.
   * @param n Number of NeoPixels in strand.
   * @param p Arduino pin number which will drive the NeoPixel data in.
   * @param t Pixel type -- add together NEO_* constants defined in
   *          Adafruit_NeoPixel.h, for example NEO_GRB+NEO_KHZ800 for
   *          NeoPixels expecting an 800 KHz (vs 400 KHz) data stream
   *          with color bytes expressed in green, red, blue order per
   *          pixel.
   */
  explicit NeoPixelController(uint16_t n, int16_t pin = 6,
                              neoPixelType type = NEO_GRB + NEO_KHZ800);

  /**
   * Stop any running shows and delete objects.
   */
  ~NeoPixelController();

  /**
   * Fade to black, or another hue.
   * This is a blocking operation.
   * @param fade_ms the approximate number of milliseconds over which to fade
   * @param r Red brightness, 0 to 255.
   * @param g Green brightness, 0 to 255.
   * @param b Blue brightness, 0 to 255.
   * @return 0 on success or a LightShow::Error on error
   */
  Error Fade(uint32_t fade_ms, uint8_t r, uint8_t g, uint8_t b) override;

  /**
   * Set all LEDs to a color
   * @param r Red brightness, 0 to 255.
   * @param g Green brightness, 0 to 255.
   * @param b Blue brightness, 0 to 255.
   * @return 0 on success or a LightShow::Error on error
   */
  Error SetLEDs(uint8_t r, uint8_t g, uint8_t b) override;

  /**
   * Set a single LED to a color
   * @param i the index of the LED to set (0-indexed)
   * @param r Red brightness, 0 to 255.
   * @param g Green brightness, 0 to 255.
   * @param b Blue brightness, 0 to 255.
   * @return 0 on success or a LightShow::Error on error
   */
  Error SetLED(uint32_t i, uint8_t r, uint8_t g, uint8_t b) override;

  /**
   * reads the local pixel values and pushing them to the NeoPixel
   * @return 0 on success or a LightShow::Error on error
   */
  Error Update() override;

 protected:
  /**
   * Fade to a color
   * This is a blocking operation.
   * @param fade_ms the approximate number of milliseconds over which to fade
   * @param c the hue color to fade to in 0xWWRRGGBB format
   * @return 0 on success or a LightShow::Error on error
   */
  Error Fade(uint32_t fade_ms, uint32_t c);

  /**
   * Fade to a color
   * This is a blocking operation.
   * @param fade_ms the approximate number of milliseconds over which to fade
   * @param p the hue color to fade to in SingleNeoPixel format
   * @return 0 on success or a LightShow::Error on error
   */
  Error Fade(uint32_t fade_ms, SingleNeoPixel p);

  /**
   * Fade to a color
   * This is a blocking operation.
   * @param fade_ms the approximate number of milliseconds over which to fade
   * @param r Red brightness, 0 to 255.
   * @param g Green brightness, 0 to 255.
   * @param b Blue brightness, 0 to 255.
   * @param w White brightness, 0 to 255.
   * @return 0 on success or a LightShow::Error on error
   */
  Error Fade(uint32_t fade_ms, uint8_t r, uint8_t g, uint8_t b, uint8_t w);

  /**
   * Set all LEDs to a color
   * @param r Red brightness, 0 to 255.
   * @param g Green brightness, 0 to 255.
   * @param b Blue brightness, 0 to 255.
   * @param w White brightness, 0 to 255.
   * @return 0 on success or a LightShow::Error on error
   */
  Error SetLEDs(uint8_t r, uint8_t g, uint8_t b, uint8_t w);

  /**
   * Set a single LED to a color
   * @param i the index of the LED to set (0-indexed)
   * @param r Red brightness, 0 to 255.
   * @param g Green brightness, 0 to 255.
   * @param b Blue brightness, 0 to 255.
   * @param w White brightness, 0 to 255.
   * @return 0 on success or a LightShow::Error on error
   */
  Error SetLED(uint32_t i, uint8_t r, uint8_t g, uint8_t b, uint8_t w);

  /// internal NeoPixel object
  std::unique_ptr<Adafruit_NeoPixel> neopixel_;

  /// a buffer containing the known state of pixels_
  std::vector<SingleNeoPixel> pixels_;

  /// the known size of the NeoPixel strip, since it is frequently referenced
  uint32_t num_pixels_;
};

}  // namespace LightShow

#endif  // LIGHTSHOW_NEOPIXEL_ENABLE

#endif  // LIGHTSHOW_NEOPIXELCONTROLLER_H
