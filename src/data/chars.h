#pragma once

#include "data_type.h"
#include "../storage/common.h"

#include <string>

namespace data {

  /**
   * @class Chars
   * @brief Represents a string of characters and provides methods for
   * serialization and deserialization.
   *
   * This class encapsulates a string value and provides functions to convert
   * it to and from byte representation. It also supports comparison and
   * concatenation operations.
   */
  class Chars : public DataType {
  private:
    int32_t len;       ///< Length of the string stored in `value`
    std::string value; ///< The actual string value

  public:
    /**
     * @brief Default constructor. Initializes an empty string.
     */
    Chars();

    /**
     * @brief Constructor initializing the length of the string.
     * @param length The length of the string.
     */
    Chars(int32_t length);

    /**
     * @brief Constructor initializing both length and value of the string.
     * @param length The length of the string.
     * @param val The actual string value.
     */
    Chars(int32_t length, std::string val);

    /**
     * @brief Serializes the string value into a byte vector.
     * @return A ByteVector representing the serialized string value.
     */
    io::ByteVector getBytes() override;

    /**
     * @brief Deserializes a ByteVector and updates the internal string value.
     * @param bytes The ByteVector containing the serialized string data.
     */
    void readBytes(io::ByteVector &bytes) override;

    /**
     * @brief Deserializes bytes from an iterator range and updates the
     * internal string value.
     * @param start The iterator pointing to the beginning of the byte data.
     * @param end The iterator pointing to the end of the byte data.
     */
    void readBytes(io::ByteVector::iterator &start,
                   io::ByteVector::iterator end) override;

    /**
     * @brief Returns the size of the serialized string data in bytes.
     * @return The size of the serialized data in bytes.
     */
    int getSizeInBytes() override;

    /**
     * @brief Retrieves the stored string value.
     * @return The current string value.
     */
    std::string getVal();

    /**
     * @brief Assignment operator for Chars.
     * @param other The Chars object to assign.
     * @return A new Chars object with the assigned value.
     */
    Chars operator=(const Chars &other) const;

    /**
     * @brief Concatenation operator for Chars.
     * @param other The Chars object to concatenate.
     * @return A new Chars object representing the concatenated string.
     */
    Chars operator+(const Chars &other) const;

    /**
     * @brief Equality operator for Chars.
     * @param other The Chars object to compare with.
     * @return True if the values are equal, false otherwise.
     */
    bool operator==(const Chars &other) const;

    /**
     * @brief Less-than operator for Chars.
     * @param other The Chars object to compare with.
     * @return True if the current value is lexicographically less than the
     * other, false otherwise.
     */
    bool operator<(const Chars &other) const;

    /**
     * @brief Greater-than operator for Chars.
     * @param other The Chars object to compare with.
     * @return True if the current value is lexicographically greater than the
     * other, false otherwise.
     */
    bool operator>(const Chars &other) const;

    /**
     * @brief Creates a Chars object from a ByteVector.
     * @param bytes The ByteVector containing the serialized string data.
     * @return A Chars object constructed from the byte data.
     */
    static Chars fromBytes(io::ByteVector &bytes);
  };
}
