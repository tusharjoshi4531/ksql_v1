#include "test.h"

#include "../../db/document.h"
#include "../../db/page.h"
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
  void testPage() {
    using db::Document;
    using db::Page;
    using db::StrictDocument;

    Page page(0);

    Document::ConstraintStore_t constraints = {
      {"name", data::CHARS}, {"age", data::INTEGER}, {"height", data::DOUBLE}};

    Document::KVStore_t values1 = {{"name", new data::Chars(30, "Tushar")},
                                   {"age", new data::Integer(21)},
                                   {"height", new data::Double(5.8)}};

    Document::KVStore_t values2 = {{"name", new data::Chars(30, "Dhroov")},
                                   {"age", new data::Integer(20)},
                                   {"height", new data::Double(4.8)}};

    StrictDocument doc1(constraints, values1);
    StrictDocument doc2(constraints, values2);

    std::cout << "\nDocument 1: " << std::endl;
    for(auto x : doc1.getKeys()) {
      auto data = doc1.get(x);
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

    std::cout << "\nDocument 2: " << std::endl;
    for(auto x : doc2.getKeys()) {
      auto data = doc2.get(x);
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

    page.addDoc(&doc1);
    page.addDoc(&doc2);

    std::cout << page.getBytes().size() << "-" << page.getRemainingSpace() << " = " << doc1.getSizeInBytes()
              << " + " << doc2.getSizeInBytes() << std::endl;

    auto pageBytes = page.getBytes();
    // return;

    io::BytesWriter writer("./data.dat");
    writer.writeData(pageBytes, 0);

    io::BytesReader reader("./data.dat");
    io::ByteVector readBytes;

    reader.readData(readBytes, 0);

    Page readPage(0);
    auto it = readBytes.begin();
    readPage.readBytes(it, readBytes.end());

    std::cout << "\nRead Documents: " << std::endl;
    auto docs = readPage.getDocs();
    for(auto doc : docs) {
      std::cout << "\nDoc: " << std::endl;
      for(auto x : doc->getKeys()) {
        auto data = doc->get(x);
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

}