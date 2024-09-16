#pragma once

#include "page.h"
#include "../storage/bytes_reader.h"
#include "../storage/bytes_writer.h"

#include <cstdint>
#include <string>

namespace db {
  class PageIO {
  private:
    std::string fileName;
    io::BytesReader reader;
    io::BytesWriter writer;

  public:
    PageIO(std::string fileName);

    Page *readPage(uint32_t pageNo);
    void writePage(Page *page);
  };
}