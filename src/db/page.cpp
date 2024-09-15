#include "page.h"
#include "document_factory.h"
#include "../storage/data_config.h"
#include <cstring>
#include <stdexcept>
#include <iostream>

namespace db {
  Page::Page() {
    auto config = io::DataConfig::getInstance();

    id = 0;
    remainingSpace = config.getBlockSizeBytes() - this->headerSize;
  }
  // Page::~Page() {
  //   for(auto doc : docs) {
  //     delete doc;
  //   }
  // }

  void Page::addDoc(Document *doc) {
    uint32_t docSize = doc->getSizeInBytes();

    if(docSize > remainingSpace) {
      throw std::runtime_error("Doc size too large for page");
    }
    // std::cout << "TEST" << std::endl;
    Document *docCopy = doc->clone();
    this->docs.push_back(docCopy);
    // return;

    this->remainingSpace -= docSize;
  }

  io::ByteVector Page::getBytes() {
    auto config = io::DataConfig::getInstance();

    uint32_t blockSize = config.getBlockSizeBytes();
    uint32_t headerSize = this->headerSize;
    uint32_t contentSize = blockSize - headerSize;

    PageHeader_t header;
    header.id = this->id;
    header.rem_space = this->remainingSpace;

    int off = 0;
    uint8_t bytes[blockSize];
    memcpy(bytes + off, &header, headerSize);

    off += headerSize;

    for(auto x : this->docs) {
      io::ByteVector docBytes = x->getBytes();
      uint32_t size = x->getSizeInBytes();

      memcpy(bytes + off, docBytes.data(), size);

      off += size;
    }

    io::ByteVector bytesVec(bytes, bytes + blockSize);

    return bytesVec;
  }

  uint32_t Page::getRemainingSpace() { return this->remainingSpace; }

  void Page::readBytes(io::ByteVector::iterator &curr,
                       io::ByteVector::iterator fin) {
    auto config = io::DataConfig::getInstance();
    uint32_t remToRead = config.getBlockSizeBytes();

    if(std::distance(curr, fin) < this->headerSize) {
      throw std::runtime_error("Not enough bytes to read page header");
    }

    PageHeader_t header;

    io::ByteVector headerBytes(curr, curr + this->headerSize);
    memcpy(&header, headerBytes.data(), this->headerSize);

    std::advance(curr, this->headerSize);
    remToRead -= headerSize;

    this->id = header.id;
    this->remainingSpace = header.rem_space;

    remToRead -= this->remainingSpace;

    while(remToRead) {
      std::cout << std::distance(curr, fin) << std::endl;
      Document *readDocument = DocumentFactory::readDocument(curr, fin);

      this->docs.push_back(readDocument);
      remToRead -= readDocument->getSizeInBytes();
    }
  }

  std::vector<Document *> Page::getDocs() { return this->docs; }
}