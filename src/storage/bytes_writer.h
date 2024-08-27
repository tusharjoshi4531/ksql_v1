#pragma once

#include "common.h"

#include <vector>
#include <string>
#include <cstdint>

namespace io {

  class BytesWriter {
  private:
    int file_descriptor;

  public:
    BytesWriter(std::string fileName);
    ~BytesWriter();
    int writeData(ByteVector &data, long blockNo);
  };
}
