#include "strict_document.h"
#include "common.h"
#include "../data/data_type_factory.h"

#include <stdexcept>
#include <cstring>
#include <iostream>

namespace db {
  StrictDocument::StrictDocument() : Document() {}
  StrictDocument::StrictDocument(std::vector<KVPair_t> &values)
      : Document(values) {}
  StrictDocument::StrictDocument(ConstraintStore_t &constraints,
                                 std::vector<KVPair_t> &values)
      : Document(constraints, values) {}
  StrictDocument::StrictDocument(std::vector<ConstraintPair_t> &constraints,
                                 std::vector<KVPair_t> &values)
      : Document(constraints, values) {}

  StrictDocument::StrictDocument(KVStore_t &values) : Document(values) {}
  StrictDocument::StrictDocument(ConstraintStore_t &constraints,
                                 KVStore_t &values)
      : Document(constraints, values) {}
  StrictDocument::StrictDocument(std::vector<ConstraintPair_t> &constraints,
                                 KVStore_t &values)
      : Document(constraints, values) {}

  void StrictDocument::set(std::string key, data::DataType *value) {
    if(this->constraints.find(key) == this->constraints.end()) {
      throw std::runtime_error(
        "Key is not present in constraints of strict document");
    }
    this->values[key] = value;
  }

  uint32_t StrictDocument::getContentSize() {
    uint32_t contentSize = 0;
    for(auto [key, value] : values) {
      contentSize += value->getSizeInBytes() + this->keyLen;
    }
    return contentSize;
  }

  uint32_t StrictDocument::getSizeInBytes() {
    int headerSize = sizeof(DocumentHeader_t);
    int bodySize = this->getContentSize();
    return headerSize + bodySize;
  }

  io::ByteVector StrictDocument::getBytes() {
    int headerSize = sizeof(DocumentHeader_t);
    int contentSize = this->getContentSize();

    DocumentHeader_t header;
    header.content_size = contentSize;
    header.doc_type = STRICT;
    header.doc_id = this->id;

    uint8_t headerBytes[headerSize];
    memcpy(headerBytes, &header, headerSize);

    io::ByteVector bytes(headerBytes, headerBytes + headerSize);

    uint8_t keyByteArray[this->keyLen];
    for(auto [key, val] : values) {
      memcpy(keyByteArray, key.c_str(), this->keyLen);

      io::ByteVector keyBytes(keyByteArray, keyByteArray + this->keyLen);
      io::ByteVector valueBytes = val->getBytes();

      bytes.insert(bytes.end(), keyBytes.begin(), keyBytes.end());
      bytes.insert(bytes.end(), valueBytes.begin(), valueBytes.end());
    }

    return bytes;
  }

  void StrictDocument::readBytes(io::ByteVector &bytes) {
    auto curr = bytes.begin();
    readBytes(curr, bytes.end());
  }

  void StrictDocument::readBytes(io::ByteVector::iterator &curr,
                                 io::ByteVector::iterator fin) {
    int headerSize = sizeof(DocumentHeader_t);
    DocumentHeader_t header;

    io::ByteVector headerBytes(curr, curr + headerSize);
    memcpy(&header, headerBytes.data(), headerSize);
    std::advance(curr, headerSize);

    this->id = header.doc_id;

    if (std::distance(curr, fin) < header.content_size) {
      throw std::runtime_error("Not enough bytes to read Document");
    }

    auto start = curr;

    while(std::distance(start, curr) < header.content_size) {
      auto next = curr;
      std::advance(next, this->keyLen);

      io::ByteVector keyBytes(curr, next);
      char keyStr[this->keyLen];
      memcpy(keyStr, keyBytes.data(), this->keyLen);

      curr = next;

      data::DataType *value
        = data::DataTypeFactory::readData(curr, fin);
      std::string key(keyStr);

      if(this->constraints.find(key) == this->constraints.end()
         || this->constraints[key] != value->getType()) {
        std::runtime_error("Read Key value does not match constraint key: "
                           + key);
      }

      this->values[key] = value;
    }
  }

  Document *StrictDocument::clone() {
    return new StrictDocument(*this);
    // return this;
  }
}