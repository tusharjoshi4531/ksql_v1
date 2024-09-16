#pragma once

#include "../data/data_type.h"
#include "../storage/common.h"

#include <map>
#include <string>
#include <vector>

namespace db {

  /**
   * @class Document
   * @brief Represents a document in a database, storing key-value pairs and
   * constraints.
   *
   * The `Document` class manages key-value pairs, where keys are strings and
   * values are pointers to `DataType` objects. It also stores constraints that
   * are mapped to specific keys. The class provides methods to serialize,
   * deserialize, and manage document content.
   */
  class Document {
  public:
#pragma pack(push, 1)
    struct DocumentHeader_t {
      uint64_t doc_id;
      uint8_t doc_type;
      uint32_t content_size;
    };
#pragma pack(pop)
    /**
     * @typedef KVStore_t
     * @brief Type definition for the key-value store.
     *
     * The key-value store maps string keys to pointers of `DataType` objects.
     */
    typedef std::map<std::string, data::DataType *> KVStore_t;

    /**
     * @typedef KVPair_t
     * @brief Type definition for key-value pairs.
     */
    typedef std::pair<std::string, data::DataType *> KVPair_t;

    /**
     * @typedef ConstraintStore_t
     * @brief Type definition for the constraint store.
     *
     * The constraint store maps string keys to integers representing
     * constraints.
     */
    typedef std::map<std::string, int> ConstraintStore_t;

    /**
     * @typedef ConstraintPair_t
     * @brief Type definition for key-constraint pairs.
     */
    typedef std::pair<std::string, int> ConstraintPair_t;

    /**
     * @brief Default constructor. Initializes an empty document.
     */
    Document();

    /**
     * @brief Constructor initializing the document with a vector of key-value
     * pairs.
     * @param kv_pairs A vector of key-value pairs to initialize the document
     * with.
     */
    Document(std::vector<KVPair_t> kv_pairs);

    /**
     * @brief Constructor initializing the document with constraints and
     * key-value pairs.
     * @param constraints A map of constraints.
     * @param kv_pairs A vector of key-value pairs.
     */
    Document(ConstraintStore_t constraints, std::vector<KVPair_t> kv_pairs);

    /**
     * @brief Constructor initializing the document with constraint pairs and
     * key-value pairs.
     * @param constraints A vector of constraint pairs.
     * @param kv_pairs A vector of key-value pairs.
     */
    Document(std::vector<ConstraintPair_t> constraints,
             std::vector<KVPair_t> kv_pairs);

    /**
     * @brief Constructor initializing the document with a key-value store.
     * @param kv_store A key-value store.
     */
    Document(KVStore_t kv_store);

    /**
     * @brief Constructor initializing the document with a constraint store and
     * key-value store.
     * @param constraints A map of constraints.
     * @param kv_store A key-value store.
     */
    Document(ConstraintStore_t constraints, KVStore_t kv_store);

    /**
     * @brief Constructor initializing the document with constraint pairs and a
     * key-value store.
     * @param constraints A vector of constraint pairs.
     * @param kv_store A key-value store.
     */
    Document(std::vector<ConstraintPair_t> constraints, KVStore_t kv_store);

    /**
     * @brief Destructor. Cleans up memory used by the document.
     */
    virtual ~Document();

    /**
     * @brief Retrieves a value associated with a key in the document.
     * @param key The key associated with the desired value.
     * @return A pointer to the `DataType` object associated with the key.
     */
    data::DataType *get(std::string key);

    /**
     * @brief Retrieves a vector of all the keys in the document.
     * @return A vector containing all the keys stored in the document.
     */
    std::vector<std::string> getKeys();

    /**
     * @brief Adds or updates a key-value pair in the document.
     * @param key The key to add or update.
     * @param value The value to associate with the key.
     */
    virtual void set(std::string key, data::DataType *value);

    /**
     * @brief Converts the document to a string
     * @return Converted document.
     */
    virtual std::string toString();

    /**
     * @brief Calculates and returns the size of the document in bytes.
     * @return The size of the document in bytes.
     */
    virtual uint32_t getSizeInBytes() = 0;

    /**
     * @brief Serializes the document into a byte vector.
     * @return A ByteVector representing the serialized document.
     */
    virtual io::ByteVector getBytes() = 0;

    /**
     * @brief Deserializes the document from a ByteVector.
     * @param bytes The ByteVector containing serialized document data.
     */
    virtual void readBytes(io::ByteVector &bytes) = 0;

    /**
     * @brief Deserializes the document from an iterator range of a ByteVector.
     * @param start The iterator pointing to the beginning of the byte data.
     * @param end The iterator pointing to the end of the byte data.
     */
    virtual void
    readBytes(io::ByteVector::iterator &start, io::ByteVector::iterator end)
      = 0;

    /**
     * @brief Clones document object and returns its pointer
     */
    virtual Document *clone() = 0;

  protected:
    /**
     * @struct DocumentHeader_t
     * @brief Represents the header for a serialized document.
     *
     * This structure is packed to ensure tight memory alignment and includes
     * the document's ID, type, and content size.
     */

    KVStore_t values;
    ConstraintStore_t constraints;
    int keyLen = 30;
    uint64_t id;
  };

}
