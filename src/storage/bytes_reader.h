#pragma once

#include "common.h"

#include <string>
#include <vector>

namespace io {
  class BytesReader {
  private:
    int file_descriptor;

  public:
    BytesReader(std::string fileName);
    ~BytesReader();
    int readData(ByteVector &data, long blockNo);
    int readData(ByteVector &data, long blockNo, int noOfBytes);
  };
}