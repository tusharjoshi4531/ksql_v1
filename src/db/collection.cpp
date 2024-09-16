#include "collection.h"
#include "../storage/data_config.h"
#include "../db/strict_document.h"
#include "../common/util.h"

namespace db {

  template <typename T>
  Collection<T>::Collection(std::string fileName) : Collection({}, fileName) {}

  template <typename T>
  Collection<T>::Collection(Document::ConstraintStore_t constraints,
                            std::string fileName)
      : remainingSpaces({}), constraints(constraints), numPages(0),
        fileName(fileName), pageIo(PageIO(fileName)) {
    auto config = io::DataConfig::getInstance();
    this->pageSize = config.getBlockSizeBytes() - sizeof(Page::PageHeader_t);
  }

  template <typename T>
  void Collection<T>::create(Document::KVStore_t &items) {
    Document *doc = static_cast<Document *>(new T(this->constraints, items));

    uint32_t docSize = doc->getSizeInBytes();

    // Find empty page
    auto it = remainingSpaces.lower_bound({docSize, -1});
    uint32_t remSize, pageNo;
    if(it != remainingSpaces.end()) {
      remSize = (*it).first;
      pageNo = (*it).second;
      remainingSpaces.erase(it);
    } else {
      remSize = this->pageSize;
      pageNo = this->numPages + 1;
    }

    db::Page *page;
    if(pageNo > this->numPages) {
      page = new Page(pageNo);
    } else {
      page = pageIo.readPage(pageNo);
    }
    // return;

    page->addDoc(doc);

    this->pageIo.writePage(page);

    remainingSpaces.insert({remSize - docSize, pageNo});

    this->numPages = std::max(this->numPages, pageNo);
  }

  template <typename T>
  Document *Collection<T>::findOne(std::string key, data::DataType *value) {
    Document *result = NULL;
    for(int pageNo = 1; pageNo <= this->numPages && result == NULL; pageNo++) {
      auto page = this->pageIo.readPage(pageNo);

      for(auto doc : page->getDocs()) {
        data::DataType *docVal = doc->get(key);

        if(docVal->equals(value)) {
          result = doc;
          break;
        }
      }

      delete page;
    }

    return result;
  }

  template <typename T> uint32_t Collection<T>::getNumPages() {
    return this->numPages;
  }

  template class Collection<StrictDocument>;
}