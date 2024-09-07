#pragma once

#include "common.h"

#include <cstdint>
#include <vector>
#include <string>

namespace io {

  /**
   * @class BytesGenerator
   * @brief A utility class for converting primitive data types to byte
   * vectors.
   *
   * The `BytesGenerator` class provides static methods to convert various
   * types (e.g., integers, floating-point numbers) into a `ByteVector`. These
   * methods are useful for serializing data into a format that can be
   * transmitted or stored.
   */
  class BytesGenerator {
  public:
    /**
     * @brief Converts a 32-bit integer into a byte vector.
     *
     * @param val The 32-bit integer to convert.
     * @return A ByteVector containing the serialized integer.
     */
    static ByteVector convert(int32_t val);

    /**
     * @brief Converts an 8-bit unsigned integer into a byte vector.
     *
     * @param val The 8-bit unsigned integer to convert.
     * @return A ByteVector containing the serialized integer.
     */
    static ByteVector convert(uint8_t val);

    /**
     * @brief Converts a double precision floating point value into a byte
     * vector.
     *
     * @param val The double value to convert.
     * @return A ByteVector containing the serialized double.
     */
    static ByteVector convert(double val);
  };

  /**
   * @class BytesParser
   * @brief A utility class for parsing primitive data types from byte vectors.
   *
   * The `BytesParser` class provides static methods to extract primitive data
   * types from a `ByteVector` or from an iterator range of a `ByteVector`.
   * This class helps in deserializing data that was serialized using the
   * `BytesGenerator`.
   */
  class BytesParser {
  public:
    /**
     * @brief Parses a 32-bit integer from a byte vector.
     *
     * @param bytes The byte vector containing the serialized integer.
     * @return The parsed 32-bit integer.
     */
    static int32_t parseInt32(ByteVector &bytes);

    /**
     * @brief Parses an 8-bit unsigned integer from a byte vector.
     *
     * @param bytes The byte vector containing the serialized integer.
     * @return The parsed 8-bit unsigned integer.
     */
    static uint8_t parseInt8(ByteVector &bytes);

    /**
     * @brief Parses a double precision floating point value from a byte vector.
     *
     * @param bytes The byte vector containing the serialized double.
     * @return The parsed double value.
     */
    static double parseDouble(ByteVector &bytes);

    /**
     * @brief Parses a string from a byte vector.
     *
     * @param bytes The byte vector containing the serialized string.
     * @return The parsed string.
     */
    static std::string parseString(ByteVector &bytes);

    /**
     * @brief Parses a 32-bit integer from a byte vector iterator range.
     *
     * @param start An iterator pointing to the beginning of the byte range.
     * @param fin An iterator pointing to the end of the byte range.
     * @return The parsed 32-bit integer.
     */
    static int32_t
    parseInt32(ByteVector::iterator start, ByteVector::iterator fin);

    /**
     * @brief Parses an 8-bit unsigned integer from a byte vector iterator
     * range.
     *
     * @param start An iterator pointing to the beginning of the byte range.
     * @param fin An iterator pointing to the end of the byte range.
     * @return The parsed 8-bit unsigned integer.
     */
    static uint8_t
    parseInt8(ByteVector::iterator start, ByteVector::iterator fin);

    /**
     * @brief Parses a double precision floating point value from a byte vector
     * iterator range.
     *
     * @param start An iterator pointing to the beginning of the byte range.
     * @param fin An iterator pointing to the end of the byte range.
     * @return The parsed double value.
     */
    static double
    parseDouble(ByteVector::iterator start, ByteVector::iterator fin);

    /**
     * @brief Parses a string from a byte vector iterator range.
     *
     * @param start An iterator pointing to the beginning of the byte range.
     * @param fin An iterator pointing to the end of the byte range.
     * @return The parsed string.
     */
    static std::string
    parseString(ByteVector::iterator start, ByteVector::iterator fin);
  };

}
