#include "document_factory.h"
#include "strict_document.h"
#include "common.h"

#include <stdexcept>
#include <cstring>

namespace db {
  template <typename T>
  T *DocumentFactory::readSpecificDocument(io::ByteVector::iterator &it,
                                           io::ByteVector::iterator fin) {
    static_assert(std::is_base_of<Document, T>::value,
                  "Generic should be a Document");

    T *x = new T();
    static_cast<Document *>(x)->readBytes(it, fin);

    return x;
  }

  Document *DocumentFactory::readDocument(io::ByteVector::iterator &it,
                                          io::ByteVector::iterator fin) {
    int remainingBytes = std::distance(it, fin);
    int headerSize = sizeof(Document::DocumentHeader_t);
    if(remainingBytes < headerSize) {
      std::runtime_error("Too less bytes to read document header");
    }

    io::ByteVector headerByes(it, it + headerSize);
    Document::DocumentHeader_t header;
    memcpy(&header, headerByes.data(), headerSize);

    uint32_t type = header.doc_type;
    if(type == STRICT) {
      return readSpecificDocument<StrictDocument> (it, fin);
    }
    return NULL;
  }
}