#pragma once

#include "common.h"

#include <string>
#include <vector>

namespace io {

  /**
   * @class BytesReader
   * @brief A utility class for reading byte data from a file.
   *
   * The `BytesReader` class provides methods to read byte data from a file,
   * given a specific block number. It allows reading the entire block or a
   * specified number of bytes from the block. This class is useful for low-level
   * file I/O operations where byte-level access to file data is required.
   */
  class BytesReader {
  private:
    int file_descriptor;

  public:
    /**
     * @brief Constructor that opens a file for reading.
     *
     * This constructor opens the file specified by `fileName` and prepares it
     * for reading.
     *
     * @param fileName The name of the file to read from.
     * @throws If the file cannot be opened, an exception or error is triggered.
     */
    BytesReader(std::string fileName);

    /**
     * @brief Destructor that closes the file.
     *
     * Ensures that the file is closed properly when the `BytesReader` object
     * is destroyed.
     */
    ~BytesReader();

    /**
     * @brief Reads data from a specific block in the file.
     *
     * This method reads data from the block identified by `blockNo` and stores
     * it in the `ByteVector` provided.
     *
     * @param data A reference to the `ByteVector` where the read data will be
     * stored.
     * @param blockNo The block number from which data should be read.
     * @return Returns the number of bytes successfully read, or an error code
     * if reading fails.
     */
    int readData(ByteVector &data, long blockNo);

    /**
     * @brief Reads a specified number of bytes from a specific block in the
     * file.
     *
     * This method reads `noOfBytes` from the block identified by `blockNo` and
     * stores it in the `ByteVector` provided.
     *
     * @param data A reference to the `ByteVector` where the read data will be
     * stored.
     * @param blockNo The block number from which data should be read.
     * @param noOfBytes The number of bytes to read from the block.
     * @return Returns the number of bytes successfully read, or an error code
     * if reading fails.
     */
    int readData(ByteVector &data, long blockNo, int noOfBytes);
  };
}
