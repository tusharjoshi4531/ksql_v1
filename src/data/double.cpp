#include "double.h"
#include "common.h"
#include "../storage/bytes_parser.h"

#include <cstring>
#include <stdexcept>
#include <string>
#include <iostream>

namespace data {
  Double::Double() : DataType(DOUBLE) { Double(0); }
  Double::Double(double val) : DataType(DOUBLE) { this->val = val; }

  double Double::getVal() { return this->val; }

  io::ByteVector Double::getBytes() {
    DoubleData_t data = {.type = DOUBLE, .value = this->val};
    int dataSize = sizeof(data);

    uint8_t byteArray[dataSize];
    std::memcpy(byteArray, &data, dataSize);

    return io::ByteVector(byteArray, byteArray + dataSize);
  }

  void Double::readBytes(io::ByteVector &bytes) {
    int typeSize = sizeof(uint8_t);
    uint8_t type
      = io::BytesParser::parseInt8(bytes.begin(), bytes.begin() + typeSize);
    if(type != DOUBLE) {
      throw std::runtime_error("Data type doesnot match Double: "
                               + std::to_string(type));
    }

    double value
      = io::BytesParser::parseDouble(bytes.begin() + typeSize, bytes.end());
    this->val = value;
  }

  void Double::readBytes(io::ByteVector::iterator &curr,
                         io::ByteVector::iterator fin) {
    int typeSize = sizeof(uint8_t);
    int doubleSize = sizeof(double);

    uint8_t type = io::BytesParser::parseInt8(curr, curr + typeSize);

    if(type != DOUBLE) {
      throw std::runtime_error("Data type doesnot match Double: "
                               + std::to_string(type));
    }

    if(std::distance(curr, fin) < this->getSizeInBytes()) {
      throw std::runtime_error("Insufficient bytes to read Double");
    }
    std::advance(curr, typeSize);

    double val = io::BytesParser::parseDouble(curr, fin);
    this->val = val;

    std::advance(curr, doubleSize);
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