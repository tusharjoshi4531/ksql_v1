#pragma once

#include "document.h"
#include "page_io.h"
#include "transaction.h"

#include <type_traits>
#include <set>
#include <iostream>

namespace db {
  template <typename T> class Collection {
  private:
    static_assert(std::is_base_of<Document, T>::value, "T must be a document");

    Document::ConstraintStore_t constraints;
    std::set<std::pair<uint32_t, uint32_t>> remainingSpaces;
    uint32_t numPages;
    std::string fileName;
    PageIO pageIo;

    uint32_t pageSize;

    Transaction transaction;

  public:
#pragma pack(push, 1)
    struct CollectionMetaData_t {
      uint32_t numPages;
      uint32_t remainingSpaces[1000];
    };
#pragma pack(pop)
    Collection(std::string fileName);
    Collection(Document::ConstraintStore_t constraints, std::string fileName);

    void create(Document::KVStore_t &items);
    Document *findOne(std::string key, data::DataType *value);
    void commit();

    uint32_t getNumPages();
  };
}