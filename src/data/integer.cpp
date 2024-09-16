#include "integer.h"
#include "common.h"
#include "../storage/bytes_parser.h"

#include <cstring>
#include <stdexcept>
#include <iostream>

namespace data {
  Integer::Integer() : DataType(INTEGER) { this->val = 0; }

  Integer::Integer(int a) : DataType(INTEGER) { this->val = a; }

  int Integer::getVal() { return this->val; }

  io::ByteVector Integer::getBytes() {
    IntegerData_t data = {.type = INTEGER, .value = this->val};
    int sz = sizeof(data);

    uint8_t byteArray[sz];
    std::memcpy(byteArray, &data, sz);

    return io::ByteVector(byteArray, byteArray + sz);
  }

  void Integer::readBytes(io::ByteVector &bytes) {
    uint8_t type = io::BytesParser::parseInt8(bytes.begin(),
                                              bytes.begin() + sizeof(type));
    if(type != INTEGER) {
      throw std::runtime_error("Data type doesnot match integer");
    }

    int32_t val
      = io::BytesParser::parseInt32(bytes.begin() + sizeof(type), bytes.end());
    this->val = val;
  }

  void Integer::readBytes(io::ByteVector::iterator &curr,
                          io::ByteVector::iterator fin) {
    uint8_t type = io::BytesParser::parseInt8(curr, curr + sizeof(type));

    if(type != INTEGER) {
      throw std::runtime_error("Data type doesnot match integer");
    }

    if(std::distance(curr, fin) < this->getSizeInBytes()) {
      throw std::runtime_error("Insufficient bytes to read integer");
    }

    std::advance(curr, sizeof(type));
    int32_t val = io::BytesParser::parseInt32(curr, curr + sizeof(int32_t));
    this->val = val;

    std::advance(curr, sizeof(int32_t));
  }

  int Integer::getSizeInBytes() { return sizeof(IntegerData_t); }

  std::string Integer::toString() {
    return std::to_string(this->val);
  }

  bool Integer::equals(DataType *data) {
    return (data->getType() == this->getType())
           && (static_cast<Integer *>(data)->getVal() == this->getVal());
  }

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