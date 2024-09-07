#pragma once

#include "../storage/common.h"
#include "data_type.h"
#include "integer.h"
#include "double.h"
#include "chars.h"

namespace data {

  /**
   * @class DataTypeFactory
   * @brief Factory class for creating instances of different data types based on serialized byte data.
   * 
   * This class provides utility methods to read and construct specific data types (such as Integer, Double, and Chars) 
   * from a range of byte data. It also offers functionality to determine and create appropriate DataType objects from 
   * serialized byte representations.
   */
  class DataTypeFactory {
  public:

    /**
     * @brief Reads a specific data type T from the given byte vector iterator range [it, fin].
     * 
     * This method reads bytes from the iterator range and constructs an object of type T.
     * The type T must be derived from the DataType class.
     * 
     * @tparam T The type of the data object to be constructed.
     * @param it An iterator pointing to the beginning of the byte data.
     * @param fin An iterator pointing to the end of the byte data.
     * @return New constructed object of type T.
     */
    template <typename T>
    static T *readSpeceficData(io::ByteVector::iterator &it,
                               io::ByteVector::iterator fin);

    /**
     * @brief Reads and constructs a DataType object from the given byte vector iterator range [it, fin].
     * 
     * This method identifies the type of the serialized data and constructs the appropriate DataType object.
     * It supports Integer, Double, and Chars data types.
     * 
     * @param it An iterator pointing to the beginning of the byte data.
     * @param fin An iterator pointing to the end of the byte data.
     * @return New constructed DataType object.
     */
    static DataType *
    readData(io::ByteVector::iterator &it, io::ByteVector::iterator fin);
  };

}
