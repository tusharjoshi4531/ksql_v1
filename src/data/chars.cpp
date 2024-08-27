#include "chars.h"
#include "common.h"
#include "../storage/common.h"
#include "../storage/bytes_parser.h"

#include <stdexcept>
#include <iostream>

namespace data {
  Chars::Chars() { this->len = 0; }
  Chars::Chars(int32_t len) { this->len = len; }
  Chars::Chars(int32_t len, std::string str) {
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
    uint8_t type = io::BytesParser::parseInt8(bytes.begin(),
                                              bytes.begin() + sizeof(type));
    if(type != CHARS) {
      throw std::runtime_error("Data type doesnot match CHARS: "
                               + std::to_string(type));
    }

    auto curr = bytes.begin();
    std::advance(curr, sizeof(type));

    int32_t len = io::BytesParser::parseInt32(curr, curr + sizeof(int32_t));

    std::advance(curr, sizeof(int32_t));

    std::string val = io::BytesParser::parseString(curr, bytes.end());

    // std::cout << val << std::endl;

    if(val.size() > len) {
      std::runtime_error("Size of string is greater than len");
    }

    this->len = len;
    this->value = val;
  }

  int Chars::getSizeInBytes() {
    return sizeof(uint8_t) + sizeof(this->len) + this->len * sizeof(char);
  }

  std::string Chars::getVal() { return this->value; }

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