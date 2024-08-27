#pragma once

#include "data_type.h"
#include "../storage/common.h"

namespace data {
  class Double : public DataType {
  private:
#pragma pack(push, 1)
    struct DoubleData_t {
      uint8_t type;
      double value;
    };
#pragma pack(pop)

    double val;

  public:
    Double();
    Double(double);

    double getVal();
    io::ByteVector getBytes() override;
    void readBytes(io::ByteVector &) override;
    int getSizeInBytes() override;

    Double operator=(const Double &) const;
    Double operator+(const Double &) const;
    Double operator-(const Double &) const;
    Double operator*(const Double &) const;
    Double operator/(const Double &) const;
    bool operator==(const Double &) const;
    bool operator<(const Double &) const;
    bool operator>(const Double &) const;

    static Double fromBytes(io::ByteVector &bytes);
  };
}