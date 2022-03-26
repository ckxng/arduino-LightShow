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

#include "Controller.h"

namespace LightShow {

Error Controller::Stop() { return this->Fade(0, 0, 0, 0); }

Error Controller::Stop(uint32_t fade_ms) {
  return this->Fade(fade_ms, 0, 0, 0);
}

int Controller::GetPresetCount() { return 5; }

Error Controller::Start(int preset) {
  if (preset < 0 || preset > this->GetPresetCount()) {
    return ShowIndexOutOfRange;
  }

  switch (preset) {
    case 0:
      this->Fade(1000, 0xFF, 0xFF, 0xFF);
      break;
    case 1:
      this->Fade(1000, 0xFF, 0x00, 0x00);
      break;
    case 2:
      this->Fade(1000, 0x00, 0xFF, 0x00);
      break;
    case 3:
      this->Fade(1000, 0x00, 0x00, 0xFF);
      break;
    case 4:
      this->Fade(1000, 0xFF, 0x00, 0x00);
      this->Fade(1000, 0x00, 0xFF, 0x00);
      this->Fade(1000, 0x00, 0x00, 0xFF);
      this->Fade(1000, 0x00, 0x00, 0x00);
      break;
    default:
      return ShowUndefined;
  }

  return NoError;
}

}  // namespace LightShow
