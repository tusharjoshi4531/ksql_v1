#include <iostream>

#include "test.h"
#include "../../data/chars.h"
#include "../../data/data_type_factory.h"
#include "../../storage/data_config.h"
#include "../../storage/bytes_writer.h"
#include "../../storage/bytes_reader.h"
#include "../../storage/bytes_parser.h"
#include "../../storage/common.h"

namespace test {
  void testString() {
    auto &config = io::DataConfig::getInstance();
    std::cout << "Data Folder: " << config.getDataDir() << std::endl;
    std::cout << "Page size: " << config.getPageSize() << std::endl;

    data::Chars test(30, "Tushar $");

    auto bytes = test.getBytes();
    std::cout << "Bytes for " << test.getVal() << ": ";
    for(auto x : bytes) {
      std::cout << (int)x << ' ';
    }
    std::cout << std::endl;

    io::BytesWriter writer("./data.dat");

    writer.writeData(bytes, 0);

    io::BytesReader reader("./data.dat");
    io::ByteVector readBytes;

    std::cout << "Size: " << test.getSizeInBytes() << std::endl;
    reader.readData(readBytes, 0, test.getSizeInBytes());

    std::cout << "Read Data: " << std::endl;
    for(auto x : readBytes)
      std::cout << (int)x << " ";
    std::cout << std::endl;

    auto readTest = data::Chars::fromBytes(readBytes);
    std::cout << "Converted Read data: " << readTest.getVal() << std::endl;
  }

  void testGenericString() {
    auto &config = io::DataConfig::getInstance();
    std::cout << "Data Folder: " << config.getDataDir() << std::endl;
    std::cout << "Page size: " << config.getPageSize() << std::endl;

    data::Chars test(30, "Name$");

    auto bytes = test.getBytes();
    std::cout << "Bytes for " << test.getVal() << ": ";
    for(auto x : bytes) {
      std::cout << (int)x << ' ';
    }
    std::cout << std::endl;

    io::BytesWriter writer("./data.dat");
    writer.writeData(bytes, 0);

    io::BytesReader reader("./data.dat");
    io::ByteVector readBytes;

    reader.readData(readBytes, 0, test.getSizeInBytes());

    std::cout << "Read Data: " << std::endl;
    for(auto x : readBytes)
      std::cout << (int)x << " ";
    std::cout << std::endl;

    auto it = readBytes.begin();
    auto readTest = data::DataTypeFactory::readData(it, readBytes.end());

    std::cout << "Converted Read data: " << ((data::Chars *)readTest)->getVal() << std::endl;
  }
}