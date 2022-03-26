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

#ifndef LIGHTSHOW_ERROR_H
#define LIGHTSHOW_ERROR_H

#include <string>

namespace LightShow {

/// Error code constants for LightShow
enum Error : int {
  /// Success / No Error
  NoError = 0x0000,
  /// An LED Strip has not been connected to the show
  NoLEDStripConnected = 0x0001,
  /// The show referenced by index does not exist
  ShowIndexOutOfRange = 0x0002,
  /// The show referenced by index exists, but is not defined
  ShowUndefined = 0x0004,
  /// The LED referenced by index does not exist
  LEDIndexOutOfRange = 0x0008
};

/**
 * describe an error code
 * @param e an error code
 * @return a description of the indicated error
 */
std::string DescribeError(Error e);

}  // namespace LightShow

#endif  // LIGHTSHOW_ERROR_H
