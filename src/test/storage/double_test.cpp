#include <iostream>

#include "test.h"
#include "../../data/double.h"
#include "../../storage/data_config.h"
#include "../../storage/bytes_writer.h"
#include "../../storage/bytes_reader.h"
#include "../../storage/bytes_parser.h"
#include "../../storage/common.h"

namespace test {

  void testDouble() {
    auto &config = io::DataConfig::getInstance();
    std::cout << "Data Folder: " << config.getDataDir() << std::endl;
    std::cout << "Page size: " << config.getPageSize() << std::endl;

    data::Double test(123.6421);

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

    auto readTest = data::Double::fromBytes(readBytes);
    std::cout << "Converted Read data: " << readTest.getVal() << std::endl;
  }

  void testNativeDouble() {
    auto &config = io::DataConfig::getInstance();
    std::cout << "Data Folder: " << config.getDataDir() << std::endl;
    std::cout << "Page size: " << config.getPageSize() << std::endl;

    double test = 123.6421;
    auto bytes = io::BytesGenerator::convert(test);

    io::BytesWriter writer("./data.dat");
    writer.writeData(bytes, 0);

    io::BytesReader reader("./data.dat");
    io::ByteVector readBytes;

    reader.readData(readBytes, 0, sizeof(double));

    std::cout << "Read Data: " << std::endl;
    for(auto x : readBytes)
      std::cout << (int)x << " ";
    std::cout << std::endl;

    auto readData = io::BytesParser::parseDouble(readBytes);
    std::cout << "Converted Read data: " << readData << std::endl;
  }
}