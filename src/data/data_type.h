#pragma once

#include <vector>
#include <cstdint>
#include "../storage/common.h"

namespace data {
  class DataType {
  public:
    virtual io::ByteVector getBytes() = 0;
    virtual void readBytes(io::ByteVector &) = 0;
    virtual int getSizeInBytes() = 0;
  };
}