#pragma once

#include "data_type.h"
#include "../storage/common.h"

namespace data {

  class Integer : public DataType {
  private:
#pragma pack(push, 1)
    struct IntegerData_t {
      uint8_t type;
      int32_t value;
    };
#pragma pack(pop)

    int32_t val;

  public:
    Integer();
    Integer(int a);

    int getVal();
    io::ByteVector getBytes() override;
    void readBytes(io::ByteVector &) override;
    int getSizeInBytes() override;

    Integer operator=(const Integer &) const;
    Integer operator+(const Integer &) const;
    Integer operator-(const Integer &) const;
    Integer operator*(const Integer &) const;
    Integer operator/(const Integer &) const;
    bool operator==(const Integer &) const;
    bool operator<(const Integer &) const;
    bool operator>(const Integer &) const;

    static Integer fromBytes(io::ByteVector &bytes);
  };
}