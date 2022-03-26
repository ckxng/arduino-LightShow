# LightShow

LightShow is a C++11 library for displaying light patterns on NeoPixel strips.

## Supported Library Versions

This library has been designed and tested using:

- fastled/FastLED@^3.5.0
- adafruit/Adafruit NeoPixel@^1.10.4

## NeoPixels vs FastLED

Both the NeoPixel and FastLED libraries are implemented as classes sharing a common LightShow::Controller interface. If
one of these libraries is not available at compile-time in your development environment, you can disable all references
to the offending library by editing LightShow.h and setting the related `#define LIGHTSHOW_*_ENABLE` entries to 0.

Please note that the FastLED implementation is somewhat awkward, as FastLED is a static implementation, while the
NeoPixel library is not. Creating more than one instance of the LightShow::FastLEDController is undefined behavior.

## Usage

FastLED version:

    #define CONFIG_NEOPIXEL_COUNT 30

    #include <Arduino.h>
    #include "FastLEDController.h"
    #include "PulseColorPreset.h"
    
    #include <memory>
    
    #define LIGHTSHOW_FASTLED_DATA_PIN PIN_A1
    auto controller =
      std::make_shared<LightShow::FastLEDController>(CONFIG_NEOPIXEL_COUNT);
    
    auto preset = LightShow::PulseColorPreset(controller, 0xFF, 0, 0, 10000, 100);
    
    void setup() {
      preset.Start();
    }
    
    void loop() {
      preset.Loop();
    }

Neopixel version:

    #define CONFIG_NEOPIXEL_COUNT 30

    #include <Arduino.h>
    #include "NeoPixelController.h"
    #include "PulseColorPreset.h"
    
    #include <memory>

    auto controller = std::make_shared<LightShow::NeoPixelController>(
        CONFIG_NEOPIXEL_COUNT, PIN_A1);
    
    auto preset = LightShow::PulseColorPreset(controller, 0xFF, 0, 0, 10000, 100);

    void setup() {
      preset.Start();
    }
    
    void loop() {
      preset.Loop();
    }

## Multiple Presets

By instantiating multiple presets, you can assign those presets to pointer, which can then be switched between and
Loop()ed on. This is a more advanced usage of the library, and requires at least a basic understanding of pointers in
C++.

    auto preset_flash =
        std::make_shared<LightShow::FlashColorPreset>(controller, 0xFF, 0, 0, 10000);
    auto preset_solid =
        std::make_shared<LightShow::SolidColorPreset>(controller, 0xFF, 0, 0);
    auto preset_pulse =
        std::make_shared<LightShow::PulseColorPreset>(controller, 0xFF, 0, 0, 10000, 100);
    auto preset_blank = std::make_shared<LightShow::Preset>();
    
    std::shared_ptr<LightShow::Preset> current_preset = preset_blank;

    void SomeCodeThatChangesPresets() {
      current_preset = preset_pulse;
    }
