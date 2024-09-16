#pragma once

#include "data_type.h"
#include "../storage/common.h"

namespace data {

  /**
   * @class Integer
   * @brief Represents a 32-bit integer data type and provides methods for
   * serialization and deserialization.
   *
   * This class encapsulates a 32-bit integer value and provides functions to
   * convert it to and from byte representation. It also supports basic
   * arithmetic operations and comparison operators.
   */
  class Integer : public DataType {
  private:
    /**
     * @struct IntegerData_t
     * @brief A structure to represent the serialized form of an integer value.
     *
     * This structure contains the type information (as a uint8_t) and the
     * actual 32-bit integer value. It is packed to ensure tight memory
     * alignment.
     */
#pragma pack(push, 1)
    struct IntegerData_t {
      uint8_t type;
      int32_t value;
    };
#pragma pack(pop)

    int32_t val;

  public:
    /**
     * @brief Default constructor. Initializes the value to 0.
     */
    Integer();

    /**
     * @brief Parameterized constructor. Initializes the object with a given
     * integer value.
     * @param a The integer value to initialize with.
     */
    Integer(int a);

    /**
     * @brief Retrieves the stored integer value.
     * @return The current integer value.
     */
    int getVal();

    /**
     * @brief Serializes the integer value into a byte vector.
     * @return A ByteVector representing the serialized integer value.
     */
    io::ByteVector getBytes() override;

    /**
     * @brief Deserializes a ByteVector and updates the internal integer value.
     * @param bytes The ByteVector containing the serialized integer data.
     */
    void readBytes(io::ByteVector &bytes) override;

    /**
     * @brief Deserializes bytes from an iterator range and updates the
     * internal integer value.
     * @param start The iterator pointing to the beginning of the byte data.
     * @param end The iterator pointing to the end of the byte data.
     */
    void readBytes(io::ByteVector::iterator &start,
                   io::ByteVector::iterator end) override;

    /**
     * @brief Returns the size of the serialized integer data in bytes.
     * @return The size of the serialized data in bytes.
     */
    int getSizeInBytes() override;

    /**
     * @brief Converts data to string.
     * @return String representation of data.
     */
    std::string toString() override;

    /**
     * @brief Checks it equals another data
     * @return The size of the serialized data in bytes.
     */
    bool equals(DataType *data) override;

    /**
     * @brief Assignment operator for Integer.
     * @param other The Integer object to assign.
     * @return A new Integer object with the assigned value.
     */
    Integer operator=(const Integer &other) const;

    /**
     * @brief Addition operator for Integer.
     * @param other The Integer object to add.
     * @return A new Integer object representing the sum.
     */
    Integer operator+(const Integer &other) const;

    /**
     * @brief Subtraction operator for Integer.
     * @param other The Integer object to subtract.
     * @return A new Integer object representing the difference.
     */
    Integer operator-(const Integer &other) const;

    /**
     * @brief Multiplication operator for Integer.
     * @param other The Integer object to multiply.
     * @return A new Integer object representing the product.
     */
    Integer operator*(const Integer &other) const;

    /**
     * @brief Division operator for Integer.
     * @param other The Integer object to divide.
     * @return A new Integer object representing the quotient.
     */
    Integer operator/(const Integer &other) const;

    /**
     * @brief Equality operator for Integer.
     * @param other The Integer object to compare with.
     * @return True if the values are equal, false otherwise.
     */
    bool operator==(const Integer &other) const;

    /**
     * @brief Less-than operator for Integer.
     * @param other The Integer object to compare with.
     * @return True if the current value is less than the other, false
     * otherwise.
     */
    bool operator<(const Integer &other) const;

    /**
     * @brief Greater-than operator for Integer.
     * @param other The Integer object to compare with.
     * @return True if the current value is greater than the other, false
     * otherwise.
     */
    bool operator>(const Integer &other) const;

    /**
     * @brief Creates an Integer object from a ByteVector.
     * @param bytes The ByteVector containing the serialized integer data.
     * @return An Integer object constructed from the byte data.
     */
    static Integer fromBytes(io::ByteVector &bytes);
  };
}
