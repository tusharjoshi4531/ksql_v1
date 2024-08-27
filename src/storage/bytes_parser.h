#pragma once

#include "common.h"

#include <cstdint>
#include <vector>
#include <string>

namespace io {

  class BytesGenerator {
  public:
    static ByteVector convert(int32_t val);
    static ByteVector convert(uint8_t val);
    static ByteVector convert(double vale);
  };

  class BytesParser {
  public:
    static int32_t parseInt32(ByteVector &bytes);
    static uint8_t parseInt8(ByteVector &bytes);
    static double parseDouble(ByteVector &bytes);
    static std::string parseString(ByteVector &bytes);

    static int32_t parseInt32(ByteVector::iterator start,
                              ByteVector::iterator fin);
    static uint8_t parseInt8(ByteVector::iterator start,
                             ByteVector::iterator fin);
    static double parseDouble(ByteVector::iterator start,
                              ByteVector::iterator fin);
    static std::string parseString(ByteVector::iterator start,
                                   ByteVector::iterator fin);
  };
}