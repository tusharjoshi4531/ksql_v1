#include "test.h"

#include "../../db/document.h"
#include "../../db/strict_document.h"
#include "../../data/common.h"
#include "../../data/chars.h"
#include "../../data/integer.h"
#include "../../data/double.h"
#include "../../storage/data_config.h"
#include "../../storage/bytes_writer.h"
#include "../../storage/bytes_reader.h"
#include "../../storage/bytes_parser.h"
#include "../../storage/common.h"

#include <iostream>

namespace test {

  void testStrictDocument() {
    auto &config = io::DataConfig::getInstance();
    std::cout << "Data Folder: " << config.getDataDir() << std::endl;
    std::cout << "Page size: " << config.getPageSize() << std::endl;

    using db::Document;
    using db::StrictDocument;

    Document::ConstraintStore_t constraints = {
      {"name", data::CHARS}, {"age", data::INTEGER}, {"height", data::DOUBLE}};

    Document::KVStore_t values = {{"name", new data::Chars(30, "Tushar")},
                                  {"age", new data::Integer(21)},
                                  {"height", new data::Double(5.8)}};

    StrictDocument doc(constraints, values);

    std::cout << "\nDocument: " << std::endl;
    for(auto x : doc.getKeys()) {
      auto data = doc.get(x);
      std::cout << x << " -> ";
      if(data->getType() == data::INTEGER) {
        std::cout << dynamic_cast<data::Integer *>(data)->getVal();
      } else if(data->getType() == data::DOUBLE) {
        std::cout << dynamic_cast<data::Double *>(data)->getVal();
      } else {
        std::cout << dynamic_cast<data::Chars *>(data)->getVal();
      }
      std::cout << std::endl;
    }

    auto docBytes = doc.getBytes();
    std::cout << "\nSize: " << docBytes.size() << std::endl;

    io::BytesWriter writer("./data.dat");
    writer.writeData(docBytes, 0);

    io::BytesReader reader("./data.dat");
    io::ByteVector readBytes;

    reader.readData(readBytes, 0, doc.getSizeInBytes() + 10);
    std::cout << "\nRead Size: " << readBytes.size() << std::endl;

    StrictDocument readDoc;
    readDoc.readBytes(readBytes);

    std::cout << "\nRead Document: " << std::endl;
    for(auto x : doc.getKeys()) {
      auto data = doc.get(x);
      std::cout << x << " -> ";
      if(data->getType() == data::INTEGER) {
        std::cout << dynamic_cast<data::Integer *>(data)->getVal();
      } else if(data->getType() == data::DOUBLE) {
        std::cout << dynamic_cast<data::Double *>(data)->getVal();
      } else {
        std::cout << dynamic_cast<data::Chars *>(data)->getVal();
      }
      std::cout << std::endl;
    }
  }
}