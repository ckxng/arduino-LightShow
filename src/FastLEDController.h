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

#ifndef LIGHTSHOW_FASTLEDCONTROLLER_H
#define LIGHTSHOW_FASTLEDCONTROLLER_H

#include "Controller.h"

#if LIGHTSHOW_FASTLED_ENABLE == 1

#include <memory>

#include "FastLED.h"

namespace LightShow {

// define LIGHTSHOW_FASTLED_DATA_PIN for the purposes of library development
// however, the app developer will need to override this
#ifndef LIGHTSHOW_FASTLED_DATA_PIN
#define LIGHTSHOW_FASTLED_DATA_PIN 0
#endif

class FastLEDController : public Controller {
 public:
  /**
   * Create a FastLED controller_ for NeoPixels.
   *
   * LIGHTSHOW_FASTLED_DATA_PIN must be defined.  For example:
   * #define LIGHTSHOW_FASTLED_DATA_PIN PIN_A1
   *
   * Creating more than one instance of this class is undefined behavior, though
   * it may be supported by a future version of this library.
   *
   * HELP WANTED: If someone more experienced with FastLED knows how to
   * implement this in a cleaner way, so that multiple FastLED controllers can
   * co-exist referenced by separate instances of this class, a PR would be most
   * welcome.
   * @param num the number of led's to control
   */
  explicit FastLEDController(uint32_t num);

  /**
   * Stop any running shows and delete objects.
   */
  ~FastLEDController();

  /**
   * Fade to a color
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
   * reads the local pixel values and pushing them to the leds_
   * @return 0 on success or a LightShow::Error on error
   */
  Error Update() override;

 protected:
  /**
   * Fade to a color
   * This is a blocking operation.
   * @param fade_ms the approximate number of milliseconds over which to fade
   * @param c the hue color to fade to
   * @return 0 on success or a LightShow::Error on error
   */
  Error Fade(uint32_t fade_ms, CRGB c);

  /**
   * a pointer to the led storage for direct access
   *
   * This controller is created by us, but not owned by us.  It will not
   * be destroyed when this object destructs.
   */
  CRGB *leds_;

  /**
   * a pointer to the underlying controller
   *
   * This controller is created by us, but not owned by us.  It will not
   * be destroyed when this object destructs.
   */
  CLEDController *controller_;

  /// the known size of the NeoPixel strip, since it is frequently referenced
  uint32_t num_leds_;

 private:
  /**
   * disallow copying by making the copy constructor private
   *
   * Copying this object does not make sense.  The data held by this object
   * are simply references to static memory in the FastLED library.
   * @param c the FastLEDController to copy
   */
  // cppcheck-suppress uninitMemberVarPrivate
  FastLEDController(const FastLEDController &c) {}

  /**
   * disallow value assignment by making the operator= private
   *
   * Copying this object does not make sense.  The data held by this object
   * are simply references to static memory in the FastLED library.
   * @param c the FastLEDController to assign
   * @return this object
   */
  // cppcheck-suppress operatorEqVarError
  FastLEDController &operator=(const FastLEDController &c) { return *this; }
};
}  // namespace LightShow

#endif  // LIGHTSHOW_FASTLED_ENABLE

#endif  // LIGHTSHOW_FASTLEDCONTROLLER_H
