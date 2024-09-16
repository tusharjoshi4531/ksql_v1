#pragma once

#include "page.h"
#include "page_io.h"

#include <string>
#include <map>

namespace db {

  class Transaction {
  private:
    enum State { ACTIVE, COMMITED };

    State state;
    std::string fileName;
    std::map<uint32_t, Page *> dirtyPages;

  public:
    Transaction(std::string fileName);

    Page *getDirtyPage(uint32_t pageNo);
    void addDirtyPage(Page *page);
    uint32_t commit();
    bool isActive();
  };
}