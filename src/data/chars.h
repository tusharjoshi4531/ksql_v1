#pragma once

#include "data_type.h"
#include "../storage/common.h"

#include <string>

namespace data {

  class Chars : public DataType {
  private:
    int32_t len;
    std::string value;

  public:
    Chars();
    Chars(int32_t);
    Chars(int32_t, std::string);

    io::ByteVector getBytes() override;
    void readBytes(io::ByteVector &) override;
    int getSizeInBytes() override;

    std::string getVal();

    Chars operator=(const Chars &) const;
    Chars operator+(const Chars &) const;
    bool operator==(const Chars &) const;
    bool operator<(const Chars &) const;
    bool operator>(const Chars &) const;

    static Chars fromBytes(io::ByteVector &bytes);
  };
}