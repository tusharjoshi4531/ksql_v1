#include "double.h"
#include "common.h"
#include "../storage/bytes_parser.h"

#include <cstring>
#include <stdexcept>
#include <string>
#include <iostream>

namespace data {
  Double::Double() { Double(0); }
  Double::Double(double val) { this->val = val; }

  double Double::getVal() { return this->val; }

  io::ByteVector Double::getBytes() {
    DoubleData_t data = {.type = DOUBLE, .value = this->val};
    int sz = sizeof(data);

    uint8_t byteArray[sz];
    std::memcpy(byteArray, &data, sz);

    return io::ByteVector(byteArray, byteArray + sz);
  }

  void Double::readBytes(io::ByteVector &bytes) {
    uint8_t type = io::BytesParser::parseInt8(bytes.begin(),
                                              bytes.begin() + sizeof(type));
    if(type != DOUBLE) {
      throw std::runtime_error("Data type doesnot match Double: "
                               + std::to_string(type));
    }

    double val = io::BytesParser::parseDouble(bytes.begin() + sizeof(type),
                                              bytes.end());
    this->val = val;
  }

  int Double::getSizeInBytes() { return sizeof(DoubleData_t); }

  // Assignemt operator
  Double Double::operator=(const Double &a) const { return Double(a.val); }

  // Addition operator
  Double Double::operator+(const Double &other) const {
    return Double(this->val + other.val);
  }

  // Subtraction operator
  Double Double::operator-(const Double &other) const {
    return Double(this->val - other.val);
  }

  // Multiplication operator
  Double Double::operator*(const Double &other) const {
    return Double(this->val * other.val);
  }

  // Division operator
  Double Double::operator/(const Double &other) const {
    return Double(this->val / other.val);
  }

  // Equality operator
  bool Double::operator==(const Double &other) const {
    return this->val == other.val;
  }

  // Less-than operator
  bool Double::operator<(const Double &other) const {
    return this->val < other.val;
  }

  // Greater-than operator
  bool Double::operator>(const Double &other) const {
    return this->val > other.val;
  }

  Double Double::fromBytes(io::ByteVector &bytes) {
    Double x;
    x.readBytes(bytes);
    return x;
  }

}