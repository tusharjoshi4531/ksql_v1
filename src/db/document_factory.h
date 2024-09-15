#pragma once

#include "document.h"

namespace db {
  class DocumentFactory {
  public:
    template <typename T>
    static T *readSpecificDocument(io::ByteVector::iterator &it,
                                   io::ByteVector::iterator fin);

    static Document *
    readDocument(io::ByteVector::iterator &it, io::ByteVector::iterator fin);
  };
}