#pragma once

#include <string>
#include <unistd.h>

#define DEFAULT_DATA_DIR "./data"     // Where data is stored
#define DEFAULT_BLOCK_SIZE 4          // Size of block in terms of page size

// Read only class

namespace io {
  class DataConfig {
  private:
    std::string data_dir;
    long page_size;
    long block_size;
    long block_size_bytes;

    DataConfig();
    
    DataConfig& operator=(const DataConfig&) = delete;

  public:
    static DataConfig &getInstance();

    std::string getDataDir();
    long getPageSize();
    long getBlockSize();
    long getBlockSizeBytes();
  };
}