#pragma once

#include "data_type.h"
#include "../storage/common.h"

namespace data {

  /**
   * @class Double
   * @brief Represents a double-precision floating point data type and provides
   * methods for serialization and deserialization.
   *
   * This class encapsulates a double value and provides functions to convert
   * it to and from byte representation.
   */
  class Double : public DataType {
  private:
    /**
     * @struct DoubleData_t
     * @brief A structure to represent the serialized form of a double value.
     *
     * This structure contains the type information (as a uint8_t) and the
     * actual double value. It is packed to ensure tight memory alignment.
     */
#pragma pack(push, 1)
    struct DoubleData_t {
      uint8_t type;
      double value;
    };
#pragma pack(pop)

    double val; ///< Stores the double value

  public:
    /**
     * @brief Default constructor. Initializes the value to 0.
     */
    Double();

    /**
     * @brief Parameterized constructor. Initializes the object with a given
     * double value.
     * @param value The double value to initialize with.
     */
    Double(double value);

    /**
     * @brief Retrieves the stored double value.
     * @return The current double value.
     */
    double getVal();

    /**
     * @brief Serializes the double value into a byte vector.
     * @return A ByteVector representing the serialized double value.
     */
    io::ByteVector getBytes() override;

    /**
     * @brief Deserializes a ByteVector and updates the internal double value.
     * @param bytes The ByteVector containing the serialized double data.
     */
    void readBytes(io::ByteVector &bytes) override;

    /**
     * @brief Deserializes bytes from an iterator range and updates the
     * internal double value.
     * @param start The iterator pointing to the beginning of the byte data.
     * @param end The iterator pointing to the end of the byte data.
     */
    void readBytes(io::ByteVector::iterator &start,
                   io::ByteVector::iterator end) override;

    /**
     * @brief Returns the size of the serialized double data in bytes.
     * @return The size of the serialized data in bytes.
     */
    int getSizeInBytes() override;

    /**
     * @brief Assignment operator for Double.
     * @param other The Double object to assign.
     * @return A new Double object with the assigned value.
     */
    Double operator=(const Double &other) const;

    /**
     * @brief Addition operator for Double.
     * @param other The Double object to add.
     * @return A new Double object representing the sum.
     */
    Double operator+(const Double &other) const;

    /**
     * @brief Subtraction operator for Double.
     * @param other The Double object to subtract.
     * @return A new Double object representing the difference.
     */
    Double operator-(const Double &other) const;

    /**
     * @brief Multiplication operator for Double.
     * @param other The Double object to multiply.
     * @return A new Double object representing the product.
     */
    Double operator*(const Double &other) const;

    /**
     * @brief Division operator for Double.
     * @param other The Double object to divide.
     * @return A new Double object representing the quotient.
     */
    Double operator/(const Double &other) const;

    /**
     * @brief Equality operator for Double.
     * @param other The Double object to compare with.
     * @return True if the values are equal, false otherwise.
     */
    bool operator==(const Double &other) const;

    /**
     * @brief Less-than operator for Double.
     * @param other The Double object to compare with.
     * @return True if the current value is less than the other, false
     * otherwise.
     */
    bool operator<(const Double &other) const;

    /**
     * @brief Greater-than operator for Double.
     * @param other The Double object to compare with.
     * @return True if the current value is greater than the other, false
     * otherwise.
     */
    bool operator>(const Double &other) const;

    /**
     * @brief Creates a Double object from a ByteVector.
     * @param bytes The ByteVector containing the serialized double data.
     * @return A Double object constructed from the byte data.
     */
    static Double fromBytes(io::ByteVector &bytes);
  };
}
