#include "bytes_writer.h"
#include "data_config.h"
#include "common.h"

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <iostream>
#include <sys/mman.h>

namespace io {
  BytesWriter::BytesWriter(std::string fileName) {
    this->file_descriptor = open(fileName.c_str(), O_RDWR);
  }

  BytesWriter::~BytesWriter() { close(this->file_descriptor); }

  int BytesWriter::writeData(ByteVector &data, long blockNo) {
    struct stat sb;

    if(fstat(this->file_descriptor, &sb) == -1) {
      std::cerr << "Incorrect descriptor" << std::endl;
      return -1;
    }

    auto &config = DataConfig::getInstance();
    long blockSize = config.getBlockSizeBytes();

    int n = data.size();
    long dataSize = n * sizeof(uint8_t);

    int offset = blockSize * blockNo;

    if(dataSize > blockSize) {
      std::cerr << "Data is too large to fit in one block" << std::endl;
      return -1;
    }

    if(offset + dataSize > sb.st_size + blockSize) {
      std::cerr << "Block no is too large" << std::endl;
      return -1;
    }

    if(offset + dataSize > sb.st_size) {
      if(ftruncate(this->file_descriptor, offset + blockSize) == -1) {
        std::cerr << "Couldn't extend file" << std::endl;
        return -1;
      }
    }

    uint8_t *file_in_memory
      = (uint8_t *)mmap(NULL, blockSize, PROT_READ | PROT_WRITE, MAP_SHARED,
                        this->file_descriptor, offset);

    for(int i = 0; i < n; i++) {
      file_in_memory[i] = data[i];
    }

    return 0;
  }
}