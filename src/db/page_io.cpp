#include "page_io.h"
#include <stdexcept>

namespace db {
  PageIO::PageIO(std::string fileName)
      : fileName(fileName), reader(io::BytesReader(fileName)),
        writer(io::BytesWriter(fileName)) {}

  Page *PageIO::readPage(uint32_t pageNo) {
    io::ByteVector pageBytes;

    if(reader.readData(pageBytes, pageNo)) {
      throw std::runtime_error("Could not read page of id: "
                               + std::to_string(pageNo)
                               + "from file: " + this->fileName);
    }

    auto page = new Page(pageNo);

    auto it = pageBytes.begin();
    auto fin = pageBytes.end();
    page->readBytes(it, fin);

    return page;
  }

  void PageIO::writePage(Page *page) {
    io::ByteVector pageBytes = page->getBytes();

    if(writer.writeData(pageBytes, page->getNo())) {
      throw std::runtime_error("Could not write page of id: "
                               + std::to_string(page->getNo())
                               + "to file: " + this->fileName);
    }
  }
}