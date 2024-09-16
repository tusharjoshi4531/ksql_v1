#include "transaction.h"
#include <iostream>

namespace db {
  Transaction::Transaction(std::string fileName) {
    this->fileName = fileName;
    this->state = State::ACTIVE;
    this->dirtyPages = std::map<uint32_t, Page *>();
  }

  Page *Transaction::getDirtyPage(uint32_t pageNo) {
    std::cout << this->dirtyPages.size() << std::endl;
    if(this->dirtyPages.find(pageNo) == this->dirtyPages.end())
      return NULL;
    return this->dirtyPages[pageNo];
  }

  void Transaction::addDirtyPage(Page *page) {
    uint32_t pageNo = page->getNo();
    this->dirtyPages[pageNo] = page;
  }

  uint32_t Transaction::commit() {
    if(this->state == State::COMMITED) {
      return 0;           
    }

    this->state = State::COMMITED;

    PageIO pageIo(this->fileName);
    
    uint32_t mxPageNo = 0;
    for(auto [pageNo, page] : dirtyPages) {
      pageIo.writePage(page);
      mxPageNo = std::max(mxPageNo, pageNo);
    }

    this->dirtyPages.clear();

    return mxPageNo;
  }

  bool Transaction::isActive() { return this->state == State::ACTIVE; }
}