#include "bytes_reader.h"
#include "data_config.h"
#include "common.h"

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <iostream>
#include <sys/mman.h>

namespace io {
  BytesReader::BytesReader(std::string fileName) {
    this->file_descriptor = open(fileName.c_str(), O_RDONLY);
  }

  BytesReader::~BytesReader() { close(this->file_descriptor); }

  int BytesReader::readData(ByteVector &data, long blockNo) {
    struct stat sb;

    if(fstat(this->file_descriptor, &sb) == -1) {
      std::cerr << "Incorrect descriptor" << std::endl;
      return -1;
    }

    auto &config = DataConfig::getInstance();
    long long blockSize = config.getBlockSizeBytes();

    int offset = blockSize * blockNo;
    
    if(offset > sb.st_size) {
      std::cerr << "Invalid block no" << std::endl;
      return -1;
    }

    auto dataSize = std::min(blockSize, sb.st_size - offset);

    uint8_t *file_in_memory = (uint8_t *)mmap(
      NULL, dataSize, PROT_READ, MAP_PRIVATE, this->file_descriptor, offset);

    int n = dataSize / sizeof(uint8_t);
    data.resize(n);

    for(int i = 0; i < n; i++) {
      data[i] = file_in_memory[i];
    }

    return 0;
  }

  int BytesReader::readData(ByteVector &data, long blockNo, int noOfBytes) {
    if (readData(data, blockNo) == -1) {
      return -1;
    }
    data.resize(noOfBytes);
    return 0;
  }
}