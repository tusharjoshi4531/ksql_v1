#include "data_type_factory.h"
#include "common.h"
#include "../storage/bytes_parser.h"

#include <stdexcept>
#include <iostream>

namespace data {
  template <typename T>
  T *DataTypeFactory::readSpeceficData(io::ByteVector::iterator &it,
                                       io::ByteVector::iterator fin) {
    static_assert(std::is_base_of<DataType, T>::value,
                  "Generic should be a Data type");

    T *x = new T();
    x->readBytes(it, fin);

    return x;
  }

  DataType *DataTypeFactory::readData(io::ByteVector::iterator &it,
                                      io::ByteVector::iterator fin) {

    int remainingBytes = std::distance(it, fin);
    if(remainingBytes < sizeof(uint8_t)) {
      std::runtime_error("Too less bytes to read type");
    }
    
    io::ByteVector typeBytes(it, it + sizeof(uint8_t));
    int type = io::BytesParser::parseInt8(typeBytes);

    if(type == INTEGER) {
      return readSpeceficData<Integer>(it, fin);
    } else if(type == DOUBLE) {
      return readSpeceficData<Double>(it, fin);
    } else if(type == CHARS) {
      return readSpeceficData<Chars>(it, fin);
    } else {
      std::runtime_error("Read incorrect type while parsing data");
    }
    return NULL;
  }
}