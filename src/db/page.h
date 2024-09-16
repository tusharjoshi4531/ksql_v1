#pragma once

#include <cstdint>
#include <vector>
#include "document.h"

namespace db {

  class Page {
  private:
    const uint32_t headerSize = sizeof(PageHeader_t);
    uint32_t no;
    uint32_t remainingSpace;
    std::vector<Document *> docs;

  public:
#pragma pack(push, 1)
    struct PageHeader_t {
      uint32_t no;
      uint32_t rem_space;
    };
#pragma pack(pop)

    Page(int no);

    void addDoc(Document *doc);
    std::vector<Document *> getDocs();
    uint32_t getNo();

    io::ByteVector getBytes();
    uint32_t getRemainingSpace();
    void
    readBytes(io::ByteVector::iterator &curr, io::ByteVector::iterator end);
  };
} // namespace db