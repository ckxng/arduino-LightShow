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

#include "Error.h"

namespace LightShow {

std::string DescribeError(Error e) {
  switch (e) {
    case NoError:
      return "No Error";
    case NoLEDStripConnected:
      return "An LED Strip has not been connected to the show";
    case ShowIndexOutOfRange:
      return "The show referenced by index does not exist";
    case ShowUndefined:
      return "The show referenced by index exists, but is not defined";
    case LEDIndexOutOfRange:
      return "The LED referenced by index does not exist";
  }
  return "Unknown error";
}

}  // namespace LightShow
