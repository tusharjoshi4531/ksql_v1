#include "integer.h"
#include "common.h"
#include "../storage/bytes_parser.h"

#include <cstring>
#include <stdexcept>

namespace data {
  Integer::Integer() { this->val = 0; }

  Integer::Integer(int a) { this->val = a; }

  int Integer::getVal() { return this->val; }

  io::ByteVector Integer::getBytes() {
    IntegerData_t data = {.type = INTEGER, .value = this->val};
    int sz = sizeof(data);

    uint8_t byteArray[sz];
    std::memcpy(byteArray, &data, sz);

    return io::ByteVector(byteArray, byteArray + sz);
  }

  void Integer::readBytes(io::ByteVector &bytes) {
    uint8_t type
      = io::BytesParser::parseInt32(bytes.begin(), bytes.begin() + sizeof(type));
    if(type != INTEGER) {
      throw std::runtime_error("Data type doesnot match integer");
    }

    int32_t val = io::BytesParser::parseInt32(bytes.begin() + sizeof(type), bytes.end());
    this->val = val;
  }

  int Integer::getSizeInBytes() { return sizeof(IntegerData_t); }

  // Assignemt operator
  Integer Integer::operator=(const Integer &a) const { return Integer(a.val); }

  // Addition operator
  Integer Integer::operator+(const Integer &other) const {
    return Integer(this->val + other.val);
  }

  // Subtraction operator
  Integer Integer::operator-(const Integer &other) const {
    return Integer(this->val - other.val);
  }

  // Multiplication operator
  Integer Integer::operator*(const Integer &other) const {
    return Integer(this->val * other.val);
  }

  // Division operator
  Integer Integer::operator/(const Integer &other) const {
    return Integer(this->val / other.val);
  }

  // Equality operator
  bool Integer::operator==(const Integer &other) const {
    return this->val == other.val;
  }

  // Less-than operator
  bool Integer::operator<(const Integer &other) const {
    return this->val < other.val;
  }

  // Greater-than operator
  bool Integer::operator>(const Integer &other) const {
    return this->val > other.val;
  }

  Integer Integer::fromBytes(io::ByteVector &bytes) {
    Integer x;
    x.readBytes(bytes);
    return x;
  }
}