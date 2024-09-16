#include "chars.h"
#include "common.h"
#include "../storage/common.h"
#include "../storage/bytes_parser.h"

#include <stdexcept>
#include <iostream>

namespace data {
  Chars::Chars() : DataType(CHARS) { this->len = 0; }
  Chars::Chars(int32_t len) : DataType(CHARS) { this->len = len; }
  Chars::Chars(int32_t len, std::string str) : DataType(CHARS) {
    this->len = len;
    this->value = str;
    if(this->value.size() > this->len) {
      throw std::runtime_error("Size of string more then assigned value");
    }
  }

  io::ByteVector Chars::getBytes() {
    uint8_t type = CHARS;
    io::ByteVector bytes(getSizeInBytes(), 0);

    int i = 0;
    bytes[i++] = type;

    std::vector<uint8_t> lenBytes = io::BytesGenerator::convert(this->len);
    for(auto byte : lenBytes) {
      bytes[i++] = byte;
    }

    for(auto chr : this->value) {
      bytes[i++] = chr;
    }

    return bytes;
  }

  void Chars::readBytes(io::ByteVector &bytes) {
    auto it = bytes.begin();
    readBytes(it, bytes.end());
  }

  void Chars::readBytes(io::ByteVector::iterator &curr,
                        io::ByteVector::iterator fin) {
    uint8_t type = io::BytesParser::parseInt8(curr, curr + sizeof(type));

    if(type != CHARS) {
      throw std::runtime_error("Data type doesnot match CHARS: "
                               + std::to_string(type));
    }

    std::advance(curr, sizeof(type));

    int32_t len = io::BytesParser::parseInt32(curr, curr + sizeof(int32_t));
    int contentSize = sizeof(char) * len;

    std::advance(curr, sizeof(int32_t));

    if(std::distance(curr, fin) < contentSize) {
      throw std::runtime_error("Not enough bytes to read CHARS ");
    }

    std::string val = io::BytesParser::parseString(curr, curr + contentSize);

    this->len = len;
    this->value = val;

    std::advance(curr, contentSize);
  }

  int Chars::getSizeInBytes() {
    return sizeof(uint8_t) + sizeof(this->len) + this->len * sizeof(char);
  }

  std::string Chars::getVal() { return this->value; }

  std::string Chars::toString() {
    return this->value;
  }

  bool Chars::equals(DataType *data) {
    return (data->getType() == this->getType())
           && (static_cast<Chars *>(data)->getVal() == this->getVal());
  }

  // Assignemt operator
  Chars Chars::operator=(const Chars &a) const {
    return Chars(a.len, a.value);
  }

  // Addition operator
  Chars Chars::operator+(const Chars &other) const {
    return Chars(len, this->value + other.value);
  }

  // Equality operator
  bool Chars::operator==(const Chars &other) const {
    return this->value == other.value;
  }

  // Less-than operator
  bool Chars::operator<(const Chars &other) const {
    return this->value < other.value;
  }

  // Greater-than operator
  bool Chars::operator>(const Chars &other) const {
    return this->value > other.value;
  }

  Chars Chars::fromBytes(io::ByteVector &bytes) {
    Chars x;
    x.readBytes(bytes);
    return x;
  }
}