#include "data_config.h"

namespace io {
  DataConfig::DataConfig() {
    data_dir = DEFAULT_DATA_DIR;
    block_size = DEFAULT_BLOCK_SIZE;
    page_size = sysconf(_SC_PAGE_SIZE);

    block_size_bytes = block_size * page_size;
  }

  DataConfig &DataConfig::getInstance() {
    static DataConfig instance;
    return instance;
  }

  std::string DataConfig::getDataDir() { return data_dir; }

  long DataConfig::getPageSize() { return page_size; }
  long DataConfig::getBlockSize() { return block_size; }
  long DataConfig::getBlockSizeBytes() { return block_size_bytes; }
}