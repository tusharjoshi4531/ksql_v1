#include "test.h"

#include "../../db/collection.h"
#include "../../db/strict_document.h"
#include "../../data/common.h"
#include "../../data/chars.h"
#include "../../data/integer.h"
#include "../../data/data_type_factory.h"
#include "../../data/double.h"
#include "../../storage/data_config.h"
#include "../../storage/bytes_writer.h"
#include "../../storage/bytes_reader.h"
#include "../../storage/bytes_parser.h"
#include "../../storage/common.h"

#include <iostream>
#include <algorithm>
#include <random>

namespace test {
  using namespace db;
  void testCollection() {
    Document::ConstraintStore_t constraints = {
      {"name", data::CHARS}, {"age", data::INTEGER}, {"height", data::DOUBLE}};
    Collection<db::StrictDocument> collection(constraints, "data.dat");

    Document::KVStore_t items
      = Document::KVStore_t({{"name", new data::Chars(30, "tushar")},
                             {"age", new data::Integer(21)},
                             {"height", new data::Double(4.7)}});

    collection.create(items);

    items = Document::KVStore_t({{"name", new data::Chars(30, "dhroov")},
                                 {"age", new data::Integer(19)},
                                 {"height", new data::Double(2.7)}});

    collection.create(items);

    auto doc1 = collection.findOne("name", new data::Chars(30, "tushar"));
    auto doc2 = collection.findOne("name", new data::Chars(30, "dhroov"));
    auto doc3 = collection.findOne("age", new data::Integer(21));
    auto doc4 = collection.findOne("age", new data::Integer(20));

    std::cout << "Document 1 ? Name == tushar" << std::endl;
    if(!doc1) {
      std::cout << "NULL" << std::endl;
    } else {
      std::cout << doc1->toString() << std::endl;
    }

    std::cout << "Document 2 ? Name == dhroov" << std::endl;
    if(!doc2) {
      std::cout << "NULL" << std::endl;
    } else {
      std::cout << doc2->toString() << std::endl;
    }

    std::cout << "Document 3 ? Age == 21" << std::endl;
    if(!doc3) {
      std::cout << "NULL" << std::endl;
    } else {
      std::cout << doc2->toString() << std::endl;
    }

    std::cout << "Document 4 ? Age == 20" << std::endl;
    if(!doc4) {
      std::cout << "NULL" << std::endl;
    } else {
      std::cout << doc2->toString() << std::endl;
    }
  }

  void
  testStrictCollectionStress(int n, std::vector<Document::KVPair_t> &queries) {
    Document::ConstraintStore_t constraints = {{"first", data::INTEGER},
                                               {"second", data::CHARS},
                                               {"third", data::DOUBLE}};
    Collection<db::StrictDocument> collection(constraints, "data.dat");

    std::vector<Document::KVStore_t> values(n);

    for(int i = 0; i < n; i++) {
      values[i]
        = Document::KVStore_t({{"first", new data::Integer(i)},
                               {"second", new data::Chars(100, "SecondValue")},
                               {"third", new data::Double(i * 4.0 / 3)}});
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(values.begin(), values.end(), g);

    for(auto value : values) {
      collection.create(value);
    }
    collection.commit();

    std::cout << "Number of pages: " << collection.getNumPages() << std::endl;

    for(auto [k, v] : queries) {
      auto doc = collection.findOne(k, v);

      std::cout << "Query: " << k << " == " << v->toString() << std::endl;
      if(doc) {
        std::cout << doc->toString() << std::endl;
      } else {
        std::cout << "NULL\n" << std::endl;
      }
    }
  }
}