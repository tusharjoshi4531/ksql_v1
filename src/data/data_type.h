#pragma once

#include <vector>
#include <cstdint>
#include "../storage/common.h"

namespace data {
  class DataType {
  private:
    int type; // Stores the type identifier for this DataType

  public:
    // Constructors
    DataType(int type);

    // Getters
    int getType();

    // Abstract methods
    virtual io::ByteVector getBytes() = 0; // Converts object to a byte vector
    virtual void readBytes(io::ByteVector &) = 0; // Reads from a byte vector
    virtual void
    readBytes(io::ByteVector::iterator &, io::ByteVector::iterator)
      = 0;                            // Reads from byte vector iterators
    virtual int getSizeInBytes() = 0; // Gets the size of the object in bytes
  };
}