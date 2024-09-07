#pragma once

#include "document.h"

namespace db {

  /**
   * @class StrictDocument
   * @brief A specialized document class that enforces constraints when setting
   * values.
   *
   * The `StrictDocument` class inherits from `Document` and enforces
   * constraints on its key-value pairs. It overrides the `set` method to
   * ensure that values adhere to predefined constraints. This class also
   * implements methods for calculating the document size, serialization, and
   * deserialization.
   */
  class StrictDocument : public Document {
  private:
    /**
     * @brief Calculates and returns the content size of the document
     * (excluding the header).
     * @return The size of the content in bytes.
     */
    int getContentSize();

  public:
    /**
     * @brief Default constructor. Initializes an empty strict document.
     */
    StrictDocument();

    /**
     * @brief Constructor initializing the document with a vector of key-value
     * pairs.
     * @param kv_pairs A vector of key-value pairs to initialize the document
     * with.
     */
    StrictDocument(std::vector<KVPair_t> &kv_pairs);

    /**
     * @brief Constructor initializing the document with constraints and
     * key-value pairs.
     * @param constraints A map of constraints.
     * @param kv_pairs A vector of key-value pairs.
     */
    StrictDocument(ConstraintStore_t &constraints,
                   std::vector<KVPair_t> &kv_pairs);

    /**
     * @brief Constructor initializing the document with constraint pairs and
     * key-value pairs.
     * @param constraints A vector of constraint pairs.
     * @param kv_pairs A vector of key-value pairs.
     */
    StrictDocument(std::vector<ConstraintPair_t> &constraints,
                   std::vector<KVPair_t> &kv_pairs);

    /**
     * @brief Constructor initializing the document with a key-value store.
     * @param kv_store A key-value store.
     */
    StrictDocument(KVStore_t &kv_store);

    /**
     * @brief Constructor initializing the document with a constraint store and
     * key-value store.
     * @param constraints A map of constraints.
     * @param kv_store A key-value store.
     */
    StrictDocument(ConstraintStore_t &constraints, KVStore_t &kv_store);

    /**
     * @brief Constructor initializing the document with constraint pairs and a
     * key-value store.
     * @param constraints A vector of constraint pairs.
     * @param kv_store A key-value store.
     */
    StrictDocument(std::vector<ConstraintPair_t> &constraints,
                   KVStore_t &kv_store);

    /**
     * @brief Adds or updates a key-value pair in the strict document,
     * enforcing constraints.
     *
     * Overrides the `set` method from `Document`. Ensures that constraints are
     * respected when setting values. If a value violates its associated
     * constraint, an error or exception is thrown (depending on the
     * implementation).
     *
     * @param key The key to add or update.
     * @param value The value to associate with the key.
     */
    void set(std::string key, data::DataType *value) override;

    /**
     * @brief Calculates and returns the total size of the document in bytes.
     *
     * This includes the header and content of the document.
     *
     * @return The size of the document in bytes.
     */
    int getSizeInBytes() override;

    /**
     * @brief Serializes the strict document into a byte vector.
     *
     * Converts the document's content and header into a byte representation
     * for storage or transmission.
     *
     * @return A ByteVector representing the serialized strict document.
     */
    io::ByteVector getBytes() override;

    /**
     * @brief Deserializes the strict document from a ByteVector.
     *
     * Reconstructs the document from serialized data contained in the provided
     * ByteVector.
     *
     * @param bytes The ByteVector containing serialized document data.
     */
    void readBytes(io::ByteVector &bytes) override;

    /**
     * @brief Deserializes the strict document from an iterator range of a
     * ByteVector.
     *
     * Reconstructs the document from an iterator range of serialized byte data.
     *
     * @param start An iterator pointing to the beginning of the byte data.
     * @param end An iterator pointing to the end of the byte data.
     */
    void readBytes(io::ByteVector::iterator &start,
                   io::ByteVector::iterator end) override;
  };

}
