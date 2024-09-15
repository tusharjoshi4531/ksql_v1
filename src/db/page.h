#pragma once

#include <cstdint>
#include <vector>
#include "document.h"

namespace db {

  class Page {
  private:
#pragma pack(push, 1)
    struct PageHeader_t {
      uint32_t id;
      uint32_t rem_space;
    };
#pragma pack(pop)
    const uint32_t headerSize = sizeof(PageHeader_t);

    uint32_t id;
    uint32_t remainingSpace;
    std::vector<Document *> docs;

  public:
    Page();
    // virtual ~Page();

    void addDoc(Document *doc);
    std::vector<Document *> getDocs();

    io::ByteVector getBytes();
    uint32_t getRemainingSpace();
    void
    readBytes(io::ByteVector::iterator &curr, io::ByteVector::iterator end);
  };
} // namespace db