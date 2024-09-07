#include "bytes_parser.h"
#include "common.h"
#include <cstring>
#include <stdexcept>

namespace io {
  ByteVector BytesGenerator::convert(int32_t val) {
    int sz = sizeof(int32_t);
    uint8_t bytesArray[sz];
    std::memcpy(bytesArray, &val, sz);

    return ByteVector(bytesArray, bytesArray + sz);
  }

  ByteVector BytesGenerator::convert(double val) {
    int sz = sizeof(double);
    uint8_t bytesArray[sz];
    std::memcpy(bytesArray, &val, sz);

    return ByteVector(bytesArray, bytesArray + sz);
  }

  ByteVector BytesGenerator::convert(uint8_t val) { return {val}; }

  int32_t BytesParser::parseInt32(ByteVector &bytes) {
    if(bytes.size() < sizeof(int)) {
      throw std::runtime_error(
        "Vector size does not match the size of int32_t");
    }

    int32_t value;
    std::memcpy(&value, bytes.data(), sizeof(int32_t));
    return value;
  }

  uint8_t BytesParser::parseInt8(ByteVector &bytes) {
    if(bytes.size() < sizeof(uint8_t)) {
      throw std::runtime_error(
        "Vector size does not match the size of uint8_t");
    }

    return bytes[0];
  }

  double BytesParser::parseDouble(ByteVector &bytes) {
    if(bytes.size() < sizeof(double)) {
      throw std::runtime_error(
        "Vector size does not match the size of double");
    }

    double value;
    std::memcpy(&value, bytes.data(), sizeof(double));
    return value;
  }

  std::string BytesParser::parseString(ByteVector &bytes) {
    char value[bytes.size()];
    std::memcpy(&value, bytes.data(), bytes.size());
    return std::string(value);
  }

  int32_t BytesParser::parseInt32(ByteVector::iterator start,
                                  ByteVector::iterator fin) {
    ByteVector bytes(start, fin);
    return parseInt32(bytes);
  }

  uint8_t BytesParser::parseInt8(ByteVector::iterator start,
                                 ByteVector::iterator fin) {
    ByteVector bytes(start, fin);
    return parseInt8(bytes);
  }

  double BytesParser::parseDouble(ByteVector::iterator start,
                                  ByteVector::iterator fin) {
    ByteVector bytes(start, fin);
    return parseDouble(bytes);
  }

  std::string BytesParser::parseString(ByteVector::iterator start,
                                       ByteVector::iterator fin) {
    ByteVector bytes(start, fin);

    return parseString(bytes);
  }
}